#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr), IsDead(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), IsDead(false),pCollider_(nullptr)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();

	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);//�������g������
			itr = childList_.erase(itr);//���X�g������폜
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();//*itr�̃����[�X���Ă�
		SAFE_DELETE(*itr);//*itr���̂�����
	}
	Release();
}

void GameObject::KillMe()
{
	IsDead = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this); //������_objName�̃I�u�W�F�N�g
	}
	else
	{
		//for (auto itr = childList_.begin();itr != childList_.end(); itr++)
		for (auto itr : childList_)
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
/// <summary>
/// �ċA�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject * �^�j</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}


GameObject* GameObject::FindObject(string _objName)
{
	
	//�������猩�āA���[�g�W���u��T���āA���̃��[�g�W���u����S���̎q�����ǂ���_objName��T��
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(_objName);
	return(result);
}

void GameObject::AddColloder(SpherCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget==this || pTarget->pCollider_==nullptr)
		return;

	/*XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
			   transform_.position_.y - pTarget->transform_.position_.y,
			   transform_.position_.z - pTarget->transform_.position_.z,0 };*/

	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());



	//XMVECTOR  dist=XMVector3D
     //�����ƃ^�[�Q�b�g�̋�������R1+R2nara
	 
	//�����A�����̃R���C�_�[�ƃ^�[�Q�b�g���Ԃ����Ă�����
	//onCollision(pTaeget)

	if (dist <= rDist)
	{
		//onCollision()���Ă�
		double p = 0;
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if (pTarget->pCollider_ != nullptr)//�����ƃ^�[�Q�b�g
		Collision(pTarget);
	//�����̎q���S���ƃ^�[�Q�b�g
	for (auto itr : childList_)
		RoundRect;
}
