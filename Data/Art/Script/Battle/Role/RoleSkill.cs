#include "Common.cs"
#include "Skill.cs"

class RoleSkill
{
    SkillType Type;
    string RoleSkillActionName = "";//���＼�ܶ���
    uint SkillTirggerIndex = 1; //�����＼�ܶ����ڼ�֡�ͷż���
    string SkillIconName = "";//����ͼ��
    uint SkillDataID = 1;//�������ݱ��
    uint SkillLogicID = 1;//�����߼����
    uint SkillLevel = 1;//���ܵȼ�
    float CoolDown = 0;//��ȴʱ��
	float EnergyConsumption = 0;//��������
	float AttackDistance = 0;//������Χ
    uint ShowColorID = 0;//������ɫ���
    string Description = "";//˵��
    


    float mTime = 0.0f;
    float mCollDown = 0.0f;//��ʼ���� ������ȴ��������󣩵���ȴʱ��
    bool mCanTrigger = false;

    

    RoleSkill()
    {

    }

    ~RoleSkill()
    {

    }

    void LoadResource()
    {
        Game::LoadAniamtion(RoleSkillActionName);
    }

    void Initialize(float coolingReduction/*����*/)
    {
        mTime = 0.0f;
        mCollDown = CoolDown*(1.0-coolingReduction);
        mCanTrigger = false;
    } 

    float GetCDProportion()
    {
        return mTime/mCollDown;
    }

    float GetCDSurplus()
    {
        return mCollDown - mTime;
    }

    bool IsCanTrigger()
    {
        return mCanTrigger;
    }

     void TriggerSkill()
     {
         mCanTrigger = false;
         mTime = 0.0f;
     }

    void Uninitialize()
    {

    }

    void Update(float dt)
    {
        if(!mCanTrigger)
        {
            if(mTime<mCollDown)
            {
                mTime += dt;
            }
            else
            {
                mTime = mCollDown;
                mCanTrigger = true;
            }
        }
    }

}