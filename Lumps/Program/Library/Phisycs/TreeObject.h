#pragma once
#include <memory>

namespace KMT
{
	// �O���錾
	template<typename T> 
	class CCell;

	//**���ؓo�^�I�u�W�F�N�g**//
	template<typename T>
	class CTreeObject
	{
	public:
		// �o�^���
		CCell<T> *pCell;
		// ����ΏۃI�u�W�F�N�g
		T *pObject;
		// �O��TreeObject�|�C���^
		CTreeObject<T> *pPrevious;
		// ����TreeObject�|�C���^
		CTreeObject<T> *pNext;
		// 
		int ID;

		// �R���X�g���N�^
		CTreeObject(int _id = 0) : ID(_id), pCell(NULL), pObject(NULL), pPrevious(NULL), pNext(NULL) { }
		// �f�X�g���N�^
		virtual ~CTreeObject() { }

		// ���烊�X�g����O���
		bool Remove()
		{
			// ���łɈ�E���Ă��鎞�͏����I��
			if(!pCell)
				return false;
			// ������o�^���Ă����ԂɎ��g��ʒm
			if(!pCell->OnRemove(this))
				return false;
			// ��E����
			// �O��̃I�u�W�F�N�g�����т���
			if(pPrevious != NULL)
				pPrevious->pNext = pNext;
			if(pNext != NULL)
				pNext->pPrevious = pPrevious;
			pPrevious = NULL;
			pNext = NULL;
			pCell = NULL;
			return true;
		}

	};

	//**�Փ˃��X�g**//
	template <typename T>
	class CCollisionList
	{
	public :
		// �R���X�g���N�^
		CCollisionList() : ppRoot_(0), position_(0), mallocSize_(0) 
		{ 
			ppRoot_ = (T**)malloc(0); 
		}
		// �f�X�g���N�^
		~CCollisionList() { }

		// �擾 : 
		inline size_t getPosition() { return position_; }
		// �擾 : ���[�g�|�C���^
		inline T** getRootPtr() { return ppRoot_; }
		// �Đݒ� : �ʒu
		inline void resetPosition() { position_ = 0; }
		
		// 
		void write(T *a, T *b)
		{
			const int COLLISIONLIST_REALLOCSIZE = 100;
			if(position_ >= mallocSize_)
			{
				ppRoot_ = (T**)realloc(ppRoot_, sizeof(T*) * (mallocSize_ + COLLISIONLIST_REALLOCSIZE));
				mallocSize_ += COLLISIONLIST_REALLOCSIZE;
			}
			ppRoot_[position_++] = a;
			ppRoot_[position_++] = b;
		}
		// 
		void refresh() { if(ppRoot_) free(ppRoot_); }

	private :
		// ���X�g���[�g�|�C���^
		T** ppRoot_;
		// �z��ʒu
		size_t	 position_;
		size_t	 mallocSize_;

	};
	
	//**���**//
	template <typename T>
	class CCell
	{
	public :
		// �R���X�g���N�^
		CCell() : pLatest(NULL) {}
		// �f�X�g���N�^
		virtual ~CCell() { if(pLatest != NULL) ResetLink(pLatest); }
		
		// �����N��S�ă��Z�b�g����
		void ResetLink(CTreeObject<T>* pTree)
		{
			if(pTree->pNext != NULL)
				ResetLink(pTree->pNext);
		}
		
		// �c���[�I�u�W�F�N�g��ǉ�
		bool Push(CTreeObject<T> *pTree)
		{
			// �����I�u�W�F�N�g�͓o�^���Ȃ�
			if(pTree == NULL) return false;
			// 2�d�o�^�`�F�b�N
			if(pTree->pCell == this) return false;
			if(pLatest == NULL)
				pLatest = pTree;
			else
			{
				// �ŐVTreeObject���X�V
				pTree->pNext = pLatest;
				pLatest->pPrevious = pTree;
				pLatest = pTree;
			}
			// ��Ԃ�o�^
			pTree->pCell = this;
			return true;
		}
		
		// �擾 : �ŐV�c���[�I�u�W�F�N�g
		inline CTreeObject<T>* getLatestObject() { return pLatest; }
		
		// �폜�����I�u�W�F�N�g���`�F�b�N
		bool OnRemove(CTreeObject<T>* pRemoveObj)
		{
			if(pLatest == pRemoveObj)
			{
				// ���̃I�u�W�F�N�g�ɑ}���ւ�
				if(pLatest != NULL)
					pLatest = pLatest->pNext;
			}
			return true;
		}

	protected :
		// �ŐV�c���[�I�u�W�F�N�g�̃|�C���^
		CTreeObject<T> *pLatest;

	};
}