#include "DXUT.h"

#include "Counter.h"

namespace KMT {

	CCounter::CCounter() : Position(), Interval(0) { }

	void CCounter::LoadFromFile(const std::string& _path)
	{
		if(Image == NULL)
			Image = CSprite::CreateFromFile(_path, DIV_X_NUM, DIV_Y_NUM);
	}

	CCounterSP CCounter::CreateCounter()
	{
		CCounterSP _obj(new CCounter());
		// �ǂݍ���
		_obj->LoadFromFile("Resource/Texture/Number.png");
		_obj->getImage()->setPlayMode(PLAYMODE::SELECT_FRAME);

		return _obj;
	}

	CCounterSP CCounter::CreateCounter(const std::string &_path)
	{
		CCounterSP _obj(new CCounter());
		// �ǂݍ���
		_obj->LoadFromFile(_path);
		_obj->getImage()->setPlayMode(PLAYMODE::SELECT_FRAME);

		return _obj;
	}

	void CCounter::Render(const ALIGN_TYPE &_type, const int &_number)
	{
		// �󂯎�������l�̕��������擾����
		int place = 0;
		char buf[MAX_NUM] = {0};

		place = sprintf_s(buf, "%d", _number);

		// ���񂹂̏ꍇ
		if(LEFT_ALI == _type) {
			for(int i = 0 ; i < place ; i++) {
				Image->Position = D3DXVECTOR3(Position.x + (i * Interval), Position.y, 0);
				Image->UpdateAnimation((buf[ i ] - '0'));
				Image->Render();
			}
		}
		
		// �E�񂹂̏ꍇ
		if(RIGHT_ALI == _type)
		{
			for( int i = 0 ; i < place ; ++i ) {
				Image->Position = D3DXVECTOR3(Position.x - ((place - i) * Interval), Position.y, 0);
				Image->UpdateAnimation((buf[ i ] - '0'));
				Image->Render();
			}
		}
	}

}