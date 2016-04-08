#include "Common.cs"
#include "Mission.cs"
#include "RoleSkill.cs"

class Role
{
    string IconName = "JarvenIVIcon.png";
    string ColorName = "HeroQualityFrame.png";
    int ColorID = 1;
    int StarCount = 1;

    string WalkName = "";
    string RunName = "";
    string IdleName = "";
    string RestName = "";
    string WinName = "";
    string HitName = "";
    string HitDownName = "";
    string HitBackName = "";
    string WaitName = "";
    string DeadName = "";
    float WalkMoveSpeed = 0.0f;
    float RunMoveSpeed = 0.0f;

    float RoleWidth = 0.0f;
    float RoleHeight = 0.0f;
    float RoleXOffset = 0.0f;
    float RoleYOffset = 0.0f;
    float RoleSpacingMin = 5.0f;//角色行走时的最小间距 默认5.0f
    float RoleSpacingMax = 100.0f;//角色行走时的最大间距 默认5.0f


    int ScriptAdd;
    int CppAdd;
    uint PropertyID = 1;
	uint PropertyLevel = 1;

    int mRoleAnimationAdd;
    int mPlayerRoleIndex = -1;

    Game::RoleType mTeam;
    State mState;
    RoleAction mAction;
    BattleState mBattleState;
    array<RoleSkill@> mSkills;//当前配置的技能
    array<uint> mSkillsSequence;//技能轮转顺序

    float mX;
    float mY;
    float mHP;
    float mMP;
    float mAttackSpeed ;
    uint mCurAttIndex;
    uint mGetSkillIndexCount;//计数器
    float mAttackTime;
    bool mIsLeft = true;//脸朝向
    bool mIsLeftTeam = true;//队伍
    Role()
    {

    }

    ~Role()
    {
        Game::RemoveAnimation(mRoleAnimationAdd);
    }

    void LoadResource()
    {
        Game::LoadAniamtion(WalkName);
        Game::LoadAniamtion(RunName);
        Game::LoadAniamtion(IdleName);
        Game::LoadAniamtion(RestName);
        Game::LoadAniamtion(WinName);
        Game::LoadAniamtion(HitName);
        Game::LoadAniamtion(HitDownName);
        Game::LoadAniamtion(HitBackName);
        Game::LoadAniamtion(WaitName);
        Game::LoadAniamtion(DeadName);
        mRoleAnimationAdd = Game::CreateAnimation(WalkName);
        Game::RunAnimation(mRoleAnimationAdd);
    }

    void Initialize()
    {
        mX = 0.0f;
        mY = 0.0f;
        mHP = Game::GetRoleProperty(CppAdd,Game::BasePropertyType::HP);
        mMP = Game::GetRoleProperty(CppAdd,Game::BasePropertyType::MP);
        WalkMoveSpeed = Game::GetRoleProperty(CppAdd,Game::BasePropertyType::MoveSpeed);
        mAttackSpeed = Game::GetRoleProperty(CppAdd,Game::BasePropertyType::AttackSpeed);
        RunMoveSpeed = WalkMoveSpeed*2;
        mCurAttIndex = 0;
        mAttackTime = 0.0f;
        mGetSkillIndexCount = 0;
    }

    void Uninitialize()
    {

    }

    float max(float a,float b)
    {
        if(a>b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    void SetPosition(float x,float y)
    {
        mX = x;
        mY = y;
        Game::SetAnimationPosition(mRoleAnimationAdd,mX,mY);
    }

    void IntoBattle()
    {
        SetState(State::Battle);
        Game::AddAnimationToLayer(0,mRoleAnimationAdd);
        SetAction(RoleAction::Walk);
    }

    void OutBattle()
    {
        SetState(State::Show);
    }
    
    void ReloadRoleAnimation( bool isRepeat,string animationName )
    {
        Game::ReloadAniamtion(mRoleAnimationAdd,isRepeat,animationName);
        Game::RemoveAnimationCallback(mRoleAnimationAdd);
    }

    bool CanTirggerSkill()
    {
        return false;
    }

    bool IsLive()
    {
        return mBattleState != BattleState::Over;
    }

    void TirggerAttackCallBack(int parameters)
    {
        uint index = mSkillsSequence[parameters];
        RoleSkill@ roleSkill = mSkills[index];
    }

    void RoleActionEndCallBack(int parameters)
    {
    
    }

    void ReLoadAction( RoleAction action )
    {
        switch(action)
        {
        case RoleAction::Walk:
             ReloadRoleAnimation(true,WalkName);
             break;
        case RoleAction::Run:
             ReloadRoleAnimation(true,RunName);
             break;
        case RoleAction::Attack:
             break;
        case RoleAction::Idle:
             ReloadRoleAnimation(true,IdleName);
             break;
        case RoleAction::Rest:
             ReloadRoleAnimation(true,RestName);
             Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
             break;
        case RoleAction::Win:
             ReloadRoleAnimation(true,WinName);
             break;
        case RoleAction::Hit:
             ReloadRoleAnimation(false,HitName);
             Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
             break;
        case RoleAction::HitDown:
             ReloadRoleAnimation(false,HitDownName);
             Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
             break;
        case RoleAction::HitBack:
             ReloadRoleAnimation(false,HitBackName);
             Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
             break;
        case RoleAction::Wait:
             ReloadRoleAnimation(true,WaitName);
             break;
        case RoleAction::Dead:
             ReloadRoleAnimation(false,DeadName);
             Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
             break;
        }
    }

    Mission@ GetMissionScript()
    {
        return cast<Mission>( Game::GetMissionScript() );
    }

    void SetTeam( bool isLeft )
    {
        mIsLeft = isLeft;
        Game::SetAnimationFlipX(mRoleAnimationAdd,!isLeft);
    }

    void SetState(State state)
    {
        if(mState==state)
        {
            return;
        }
        mState = state;
    }

    void SetBattleState(BattleState state)
    {
        if(mBattleState==state)
        {
            return;
        }

        
        switch(state)
        {
        case BattleState::Normal:
             break;
        case BattleState::Pause:
             break;
        case BattleState::Over:
             break;
        }
        mBattleState = state;
    }

    void SetAction( RoleAction action )
    {
        if(mAction==action)
        {
            return;
        }
        ReLoadAction(action);
        mAction = action;
    }

    void Move( float dt,float speed ,Role@ frontRole)
    {
        float desSpeed = speed;
        Mission@ mission = GetMissionScript();

        if( frontRole!=null &&( mAction == RoleAction::Run || mAction == RoleAction::Walk ) )
        {
            bool isBrake = false;
            bool isComeOn = false;
            if( mIsLeft )
            {
                if(frontRole.GetLeft() - GetRight() < RoleSpacingMin )
                {
                    isBrake = true;
                }
                else if( frontRole.GetLeft() - GetRight() > RoleSpacingMax )
                {
                    isComeOn = true;
                }
            }
            else
            {
                if(GetLeft() - frontRole.GetRight() < RoleSpacingMin )
                {
                    isBrake = true;
                }
                else if( GetLeft() - frontRole.GetRight() > RoleSpacingMax )
                {
                    isComeOn = true;
                }
            }
        
           if(isBrake)
           {
               switch(frontRole.mAction)
               {
               case RoleAction::Walk:
                    if(frontRole.WalkMoveSpeed<WalkMoveSpeed)
                    {
                        desSpeed = frontRole.WalkMoveSpeed;
                    }
                    SetAction(RoleAction::Walk);
                    break;
               case RoleAction::Run:
                    desSpeed = frontRole.RunMoveSpeed;
                    if(frontRole.RunMoveSpeed<WalkMoveSpeed)
                    {
                        desSpeed = frontRole.RunMoveSpeed;
                    }
                    SetAction(RoleAction::Walk);
                    break;
               case RoleAction::Attack:
               case RoleAction::Idle:
               case RoleAction::Rest:
               case RoleAction::Win:
               case RoleAction::Hit:
               case RoleAction::HitDown:
               case RoleAction::HitBack:
               case RoleAction::Wait:
                    desSpeed = 0;
                    SetAction(RoleAction::Rest);
               case RoleAction::Dead:
                    break;
               }
           }

           if(isComeOn)
           {
                if(mAction == RoleAction::Run)
                {
                    mission.WaitForMe();
                }
                else if(mAction == RoleAction::Walk)
                {
                    SetAction(RoleAction::Run);
                }
           }
        }

        desSpeed = speed + mission.mCamerSpeed ;
        mX += desSpeed*dt;
        SetPosition(mX,mY);
    }

    void Update(float dt,Role@ frontRole)
    {
        if( mState != State::Battle )
        {
            return;
        }

        switch(mBattleState)
        {
        case BattleState::Normal:
            UpdateSkills(dt);
            switch(mAction)
            {
            case RoleAction::Walk:
                 mAttackTime += dt;
                 Move(dt,WalkMoveSpeed,frontRole);
                 UpdateAttackTargetLogic();
                 break;
            case RoleAction::Run:
                 mAttackTime += dt;
                 Move(dt,RunMoveSpeed,frontRole);
                 UpdateAttackTargetLogic();
                 break;
            case RoleAction::Attack:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 break;
            case RoleAction::Idle:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 UpdateAttackTargetLogic();
                 break;
            case RoleAction::Rest:
                 mAttackTime += dt;
                if(frontRole!=null)
                {
                    if( frontRole.mAction == RoleAction::Walk || frontRole.mAction == RoleAction::Run )
                    {
                        SetAction(RoleAction::Walk);
                    }
                }
                 Move(dt,0,null);
                 break;
            case RoleAction::Win:
                 break;
            case RoleAction::Hit:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 break;
            case RoleAction::HitDown:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 break;
            case RoleAction::HitBack:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 break;
            case RoleAction::Wait:
                 mAttackTime += dt;
                 Move(dt,0,null);
                 break;
            case RoleAction::Dead:
                 Move(dt,0,null);
                 break;
            }
             break;
        case BattleState::Pause:
             break;
        case BattleState::Over:
            {
//                 Mission@ mission = GetMissionScript();
//                 mission.OverRole(this);
            }
             break;
        }
    }

    float GetLeft()
    {
        if(mIsLeft)
        {
            return mX + RoleXOffset;
        }
        else
        {
            return mX - ( RoleWidth + RoleXOffset );
        }
    }

    float GetRight()
    {
        if(mIsLeft)
        {
            return mX + ( RoleWidth + RoleXOffset );
        }
        else
        {
            return mX - RoleXOffset;
        }
    }

    void UpdateSkills(float dt)
    {
        for(uint i = 0;i<mSkills.length;i++)
        {
            RoleSkill @skill = mSkills[i];
            skill.Update(dt);
        }
    }

    void UpdatePosition()
    {
//          Mission@ mission = GetMissionScript();
//          for(int i=0;i<mission.mActiveRoles.length;i++)
//          {
//              Role @role = mission.mActiveRoles[i];
//          }
         
    }

    RoleSkill@ GetSkillIndex(float surplusTime)
    {
       if(mSkillsSequence.length==0)
       {
          Log(" Skills Sequence length Error ");
          return null;
       }
       uint index = mSkillsSequence[mCurAttIndex];
       if( index >= mSkills.length )
       {
          Log(" Skills  Index Error ");
          return null;
       }

       RoleSkill@ roleSkill = mSkills[index];
       if( surplusTime >= roleSkill.GetCDSurplus() )
       {
            mGetSkillIndexCount = 0;
            return roleSkill;
       }
       else
       {
           if(mGetSkillIndexCount>=mSkillsSequence.length)
           {
                mGetSkillIndexCount = 0;
                return null;
           }
            mGetSkillIndexCount++;
            mCurAttIndex ++;
            mCurAttIndex = mCurAttIndex % mSkillsSequence.length;
            return GetSkillIndex(surplusTime);
       }
    }

    void UpdateAttackTargetLogic()
    {
        Mission@ mission = GetMissionScript();
        Role@ role = mission.GetFirstRole( !mIsLeftTeam ) ;
        if( role == null )
        {
//             if( mission.IsLeftMove == mIsLeftTeam )
//             {
//                 if(mIsLeftTeam)
//                 {
//                     if( mX - Game::GetSceneWidth()/2.0f > 10.0f )
//                     {
//                         SetAction(RoleAction::Idle);
//                     }
//                     else if(Game::GetSceneWidth()/2.0f - mission.GetFirstRole( mIsLeftTeam ).mX > 10.0f)
//                     {
//                         //TODO:有可能是奔跑
//                         //SetAction(RoleAction::Walk);
//                     }
//                 }
//                 else
//                 {
//                     if(mX - Game::GetSceneWidth()/2.0f < -10.0f)
//                     {
//                         SetAction(RoleAction::Idle);
//                     }
//                     else
//                     {
//                         //TODO:有可能是奔跑
//                         //SetAction(RoleAction::Walk);
//                     }
//                 }
//             }
            return;
        }
        else
        {
            float surplusTime = max(0.0f,1.0f/mAttackSpeed - mAttackTime);
            RoleSkill@ roleSkill = GetSkillIndex( surplusTime );
            if(roleSkill != null)
            {
                switch(roleSkill.Type)
                {
                case SkillType::AttackEnemy:
                    {
                        if(mIsLeft)
                        {
                            if( role.GetLeft() - GetRight() <= roleSkill.AttackDistance )
                            {
                                if( mAttackTime > 1.0f/mAttackSpeed )
                                {
                                    roleSkill.TriggerSkill();
                                    mCurAttIndex++;
                                    mAttackTime = 0.0f;
                                    SetAction(RoleAction::Attack);
                                    ReloadRoleAnimation(false,roleSkill.RoleSkillActionName);
                                    Game::RegisterAnimationEvent( mRoleAnimationAdd,roleSkill.SkillTirggerIndex,ScriptAdd,"TirggerAttackCallBack",mCurAttIndex );
                                    Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
                                }
                                else
                                {
                                    SetAction(RoleAction::Idle);
                                }
                            }
                        }
                        else
                        {
                            
                            if( GetLeft() - role.GetRight() <= roleSkill.AttackDistance )
                            {
                                if( mAttackTime > 1.0f/mAttackSpeed)
                                {
                                    roleSkill.TriggerSkill();
                                    mCurAttIndex++;
                                    mAttackTime = 0.0f;
                                    SetAction(RoleAction::Attack);
                                    ReloadRoleAnimation(false,roleSkill.RoleSkillActionName);
                                    Game::RegisterAnimationEvent( mRoleAnimationAdd,roleSkill.SkillTirggerIndex,ScriptAdd,"TirggerAttackCallBack",mCurAttIndex );
                                    Game::RegisterAnimationEvent( mRoleAnimationAdd,999,ScriptAdd,"RoleActionEndCallBack",0 );
                                }
                                else
                                {
                                    SetAction(RoleAction::Idle);
                                }
                            }
                        }
                    }
                    
                    break;
                case SkillType::HelpSelf:
                    break;
                }

                
            }
            else
            {
           
            }
            
        }
        
        
    }

}