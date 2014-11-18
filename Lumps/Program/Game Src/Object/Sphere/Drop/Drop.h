#pragma once

#include <memory>
#include "../Sphere.h"

class CDrop;
typedef std::shared_ptr<CDrop> CDropSP;

// �������I�u�W�F�N�g
class CDrop : public CSphere
{
public :
	// �f�X�g���N�^
	~CDrop() { }
	// ����
	static CDropSP Create();
	// �擾 : ���ʉ�]
	CQuaternion getFrontRotation() const;

private :
	// ��]���x
	int rotateSpeed;

	// �R���X�g���N�^
	CDrop();
	// �s���̍X�V
	void updateAction(CCommand &command, CState &state);
	// ���C�t�����Ǘ�
	void manageLife(CState& state);

protected:
	// �h���N���X�ŗL�̍X�V����
	void subUpdate(CCommand &command, CState &state);
	// ���̔��f
	void subApplyParameter();

} ;