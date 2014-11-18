#pragma once

#include <windows.h>
#include <memory>
#include <list>
#include "TreeObject.h"

namespace KMT {

	//**���`�l���؋�ԕ����Ǘ��N���X**//
	const int CLINERQUADTREEMANAGER_LEVELMAX_ = 9;
	template <typename T> 
	class CLinerQuadTreeManager
	{
	public :
		// �R���X�g���N�^
		CLinerQuadTreeManager(): Level_(0), Width_(0.0f), Height_(0.0f), Left_(0.0f), Top_(0.0f), unitWidth_(0.0f), unitHeight_(0.0f), CellNum_(0), Dimension_(0)
		{
			// �e���x���ł̋�Ԑ����Z�o
			Pow_[0] = 1;
			for(int i = 1; i < CLINERQUADTREEMANAGER_LEVELMAX_ + 1; i++)
				Pow_[i] = Pow_[i - 1] * 4;
		}
		// �f�X�g���N�^
		virtual ~CLinerQuadTreeManager()
		{
			for(DWORD i = 0; i < CellNum_; i++){
				if(ppCellArray_[i] != NULL)
					delete ppCellArray_[i];
			}
			delete[] ppCellArray_;
		}
		
		// ���`�l���ؔz����\�z����
		bool Initialize(size_t _Level, float _Left, float _Top, float _Right, float _Bottom)
		{
			//�ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
			if(_Level >= CLINERQUADTREEMANAGER_LEVELMAX_)
				return false;
			// Level���x��(0��_)�̔z��쐬
			CellNum_ = (Pow_[_Level + 1] - 1) / 3;
			ppCellArray_ = new CCell<T>*[CellNum_];
			ZeroMemory(ppCellArray_, sizeof(CCell<T>*) * CellNum_);
			// �̈��o�^
			Left_ = _Left;
			Top_ = _Top;
			Width_ = _Right - _Left;
			Height_ = _Bottom - _Top;
			unitWidth_ = Width_ / (1 << _Level);
			unitHeight_ = Height_ / (1 << _Level);

			Level_ = _Level;

			return true;
		}
		
		// �o�^ : �I�u�W�F�N�g
		bool Register(float _Left, float _Top, float _Right, float _Bottom, CTreeObject<T>* _pTree)
		{
			// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
			DWORD elem = getMortonNumber(_Left, _Top, _Right, _Bottom);
			if(elem < CellNum_)
			{
				// ��Ԃ��Ȃ��ꍇ�͐V�K�쐬
				if(!ppCellArray_[elem])
					CreateCell(elem);
				return ppCellArray_[elem]->Push(_pTree);
			}
			// �o�^���s
			return false;
		}
		
		// �Փ˔��胊�X�g���쐬����
		DWORD getAllCollisionList(CCollisionList<T> **_ColList)
		{
			// ���X�g(�z��)�͕K��������
			CollisionList_.resetPosition();
			// ���[�g��Ԃ̑��݂��`�F�b�N
			if(ppCellArray_[0] == NULL)
				// ��Ԃ����݂��Ă��Ȃ�
				return 0;
			// ���[�g��Ԃ�����
			std::list<T*> ColStac;
			getCollisionList(0, ColStac);

			*_ColList = &CollisionList_;

			return (DWORD)CollisionList_.getPosition();
		}

	private :
	protected :
		// �����炭����
		size_t Dimension_;
		// ���`��ԃ|�C���^�z��
		CCell<T> **ppCellArray_;
		// �ׂ��搔�l�z��
		size_t Pow_[CLINERQUADTREEMANAGER_LEVELMAX_+1];
		// �̈��XY����
		float Width_, Height_;
		// �̈�̍��� (X���ŏ��l)
		float Left_;
		// �̈�̏㑤 (Y���ŏ��l)
		float Top_;
		// �ŏ����x����Ԃ̕��P��
		float unitWidth_;
		// �ŏ����x����Ԃ̍��P��
		float unitHeight_;
		// ��Ԃ̐�
		DWORD CellNum_;
		// �ŉ��ʃ��x��
		size_t Level_;
		// �Փ˃��X�g
		CCollisionList<T> CollisionList_;

		// ��ԓ��ŏՓ˃��X�g���쐬
		bool getCollisionList(DWORD elem, std::list<T*> &_ColStac)
		{
			std::list<T*>::iterator it;
			// 1, ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
			CTreeObject<T>* pTree1 = ppCellArray_[elem]->getLatestObject();
			while(pTree1 != NULL)
			{
				CTreeObject<T>* pTree2 = pTree1->pNext;
				while(pTree2 != NULL)
				{
					CollisionList_.write(pTree1->pObject, pTree2->pObject);
					pTree2 = pTree2->pNext;
				}
				// 2, �Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
				for(it = _ColStac.begin(); it != _ColStac.end(); it++)
					CollisionList_.write(pTree1->pObject, *it);
				pTree1 = pTree1->pNext;
			}

			bool isChild = false;
			// 3, �q��ԂɈړ�
			DWORD ObjNum = 0;
			DWORD NextElement;
			for(DWORD i = 0; i < 4; i++)
			{
				NextElement = (elem * 4) + 1 + i;
				if(NextElement < CellNum_ && ppCellArray_[(elem * 4) + 1 + i])
				{
					if(!isChild)
					{
						// 4, �o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
						pTree1 = ppCellArray_[elem]->getLatestObject();
						while(pTree1 != NULL)
						{
							_ColStac.push_back(pTree1->pObject);
							ObjNum++;
							pTree1 = pTree1->pNext;
						}
					}
					isChild = true;
					// �q��Ԃ�
					getCollisionList((elem * 4) + 1 + i, _ColStac);
				}
			}
			// 5, �X�^�b�N����I�u�W�F�N�g���O��
			if(isChild)
				for(DWORD i = 0; i < ObjNum; i++)
					_ColStac.pop_back();
			return true;
		}
		
		// ��Ԃ𐶐�
		bool CreateCell(DWORD elem)
		{
			// �����̗v�f�ԍ�
			while(!ppCellArray_[elem])
			{
				// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
				ppCellArray_[elem] = new CCell<T>;
				// �e��ԂɃW�����v
				elem = (elem - 1) >> 2;
				if(elem >= CellNum_)
					break ;
			}
			return true;
		}
		
		// ���W�����Ԕԍ����Z�o
		DWORD getMortonNumber(float _Left, float _Top, float _Right, float _Bottom)
		{
			// �ŏ����x���ɂ�����e���ʒu���Z�o
			DWORD LT = getPointElement(_Left, _Top);
			DWORD RB = getPointElement(_Right, _Bottom);
			// ��Ԕԍ��̔r���I�_���a���珊�����x�����Z�o
			DWORD Def = RB ^ LT;
			size_t HiLevel = 0;
			for(size_t i = 0; i < Level_; i++)
			{
				DWORD Check = (Def >> (i * 2)) & 0x3;
				if(Check != 0)
					HiLevel = i + 1;
			}
			DWORD SpaceNum = RB >> (HiLevel * 2);
			DWORD AddNum = (Pow_[Level_ - HiLevel] - 1) / 3;
			SpaceNum += AddNum;
			if(SpaceNum > CellNum_)
				return 0xffffffff;
			return SpaceNum;
		}
		
		// �r�b�g����
		DWORD BitSeparate32(DWORD n)
		{
			n = (n | (n << 8)) & 0x00ff00ff;
			n = (n | (n << 4)) & 0x0f0f0f0f;
			n = (n | (n << 2)) & 0x33333333;
			return (n | (n << 1)) & 0x55555555;
		}
		
		// 2D���[�g����Ԕԍ��Z�o�֐�
		WORD get2DMortonNumber(WORD x, WORD y) { return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1)); }
		
		// ���W�����`�l���ؗv�f�ԍ��ϊ��֐�
		inline DWORD getPointElement(float posX, float posY) { return get2DMortonNumber((WORD)((posX - Left_) / unitWidth_), (WORD)((posY - Top_) / unitHeight_)); }

	};

}