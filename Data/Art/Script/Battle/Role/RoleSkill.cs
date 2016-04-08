#include "Common.cs"
#include "Skill.cs"

class RoleSkill
{
    SkillType Type;
    string RoleSkillActionName = "";//人物技能动画
    uint SkillTirggerIndex = 1; //在人物技能动画第几帧释放技能
    string SkillIconName = "";//技能图标
    uint SkillDataID = 1;//技能数据编号
    uint SkillLogicID = 1;//技能逻辑编号
    uint SkillLevel = 1;//技能等级
    float CoolDown = 0;//冷却时间
	float EnergyConsumption = 0;//能量消耗
	float AttackDistance = 0;//攻击范围
    uint ShowColorID = 0;//能量颜色编号
    string Description = "";//说明
    


    float mTime = 0.0f;
    float mCollDown = 0.0f;//初始化后 （和冷却减缩计算后）的冷却时间
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

    void Initialize(float coolingReduction/*冷缩*/)
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