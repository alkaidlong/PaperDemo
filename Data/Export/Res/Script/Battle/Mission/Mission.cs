#include "Role.cs"
#include "Common.cs"

class Mission
{
    float BGMoveTime = 0.0f;//背景移动时间
    bool IsLeftMove = true;
    bool IsNPCBattle = false;

    array<int> mBGAdds;
    array<float> mBGWidth;
    array<float> mBGSpeed;
    array<float> mBGPositionx;

    float mCameraPositionX = 0.0f;
    float mCamerSpeed = 0.0f;
    float mSceneWidth = 0.0f;
    uint CamerIDInMissionProgress = 1;

    array<Role@> mMissionRoles;
    array<Role@> mPlayerRoles;
    array<Role@> mActiveRoles;//当前活跃角色

//    bool mIsCreateEnemgy;
    float mTime = 0.0f;

 //   Role @mTempRoleRef;
 //   bool asdoijfoad = false;

    Mission() 
    {
    
    }

    ~Mission() 
    {
    
    }

    void LoadResource() 
    {
        
    }

    void Initialize() 
    {
        for(uint i = 0;i<mPlayerRoles.length;i++)
        {
            Role @roleRef = mPlayerRoles[i];
            roleRef.SetPosition((5-roleRef.mPlayerRoleIndex)*100.0f,0);
        }
        Game::AddMissionProgressElement(CamerIDInMissionProgress,Game::RoleType::Player,0.0f);
        for(uint i = 0;i<mBGAdds.length;i++)
        {
            float w = GetLayerWidth(mBGAdds[i]);
            mBGWidth.insertLast(w);
            mBGPositionx.insertLast(0);
            if(i==1)
            {
                mSceneWidth = w;
            }
        }
        for(uint i = 0;i<mBGAdds.length;i++)
        {
            float w = mBGWidth[i];
            float s = w/mSceneWidth;
            mBGSpeed.insertLast(s);
        }
    }

    void Uninitialize() 
    {
        
    }

    void AddMissionRoles(int roleScriptAdd) 
    {
        Role @roleRef = cast<Role>(Game::GetScriptHandle(roleScriptAdd));
        mMissionRoles.insertLast(roleRef);
        mActiveRoles.insertLast(roleRef);
    }

    void AddPlayerRoles(int roleScriptAdd,int index) 
    {
        Role @roleRef = cast<Role>(Game::GetScriptHandle(roleScriptAdd));
        mPlayerRoles.insertLast(roleRef);
        roleRef.mPlayerRoleIndex = index;
        mActiveRoles.insertLast(roleRef);
    }

    void OverRole( Role @roleRef )
    {
        int index = mActiveRoles.find(roleRef);
        if( index != -1)
        {
            mActiveRoles.removeAt(index);
        }
    }

    void UpdateCamerMoveSpeed()
    {
        Role @roleRef = GetFirstRole(IsLeftMove);
        mCamerSpeed = 0.0f;
        if( roleRef != null )
        {
            if( IsLeftMove )
            {
                if( Game::GetSceneWidth()/2.0f - roleRef.mX < -1.0f )
                {
                    if(-mCameraPositionX<mSceneWidth)
                    {
                        if( roleRef.mState == RoleAction::Walk )
                        {
                            mCamerSpeed = -roleRef.WalkMoveSpeed;
                        }
                        else
                        {
                            mCamerSpeed = -mSceneWidth/BGMoveTime;
                        }
                    }
                    else
                    {
                        BGMoveDone();
                    }
                }
            }
            else
            {
                if(Game::GetSceneWidth()/2.0f - roleRef.mX > 1.0f)
                {
                    if( roleRef.mState == RoleAction::Walk )
                    {
                        mCamerSpeed = roleRef.WalkMoveSpeed;
                    }
                    else
                    {
                        mCamerSpeed = mSceneWidth/BGMoveTime;
                    }
                }
            }
        } 
    }

    void MoveCamer(float dt)
    {
        mCameraPositionX += mCamerSpeed*dt;
        
        for(uint i = 0;i<mBGAdds.length;i++)
        {
            mBGPositionx[i] += mBGSpeed[i]*mCamerSpeed*dt;
            Game::SetLayerPosition(mBGAdds[i],mBGPositionx[i],0.0f);
        }
        float cameraPos = -mCameraPositionX/mSceneWidth;
        Game::SetMissionProgressElementPosition(CamerIDInMissionProgress,cameraPos);


//         if(!mIsCreateEnemgy&&mTime >= 3.0f)
//         {
//             mIsCreateEnemgy = true;
//             @mTempRoleRef  = cast<Role>(Game::CreateRoleAndAddToMission(20001,Game::RoleType::Monster));
//             mTempRoleRef.SetPosition(800.0f,0);
//             mTempRoleRef.SetTeam(false);
//             mTempRoleRef.SetAction(RoleAction::Idle);
//         }
    }

    void Update(float dt) 
    {
        mTime+=dt;
        UpdateCamerMoveSpeed();
        MoveCamer(dt);
//          if(!asdoijfoad&&mIsCreateEnemgy&&mTime>5.0f)
//          {
//              asdoijfoad = true;
//              //mTempRoleRef.mHP = -1.0f;
// 
//              mTempRoleRef.SetPosition(1500.0f,0);
//              Role @roleRef = GetFirstRole(IsLeftMove);
//              roleRef.SetPosition(1300.0f,0);
//          }
// 
//         if(mIsCreateEnemgy&&mTime>10.0f)
//          {
//              mTempRoleRef.mHP = -1.0f;
//          }

    }

    void BGMoveDone() 
    {
        mCamerSpeed = 0.0f;
        Game::SetMissionProgressElementPosition(CamerIDInMissionProgress,1.0f);
    }

    float GetLayerWidth( int bgAdd )
    {
        return Game::GetLayerWidth(bgAdd)-Game::GetSceneWidth();
    }

    Role@ GetFirstRole(bool isLeft)
    {
        Role@ result = null;
        float max = 0.0f;

        if( !isLeft )
        {
            max = Game::GetSceneWidth();
        }

        for( uint i = 0 ; i<mActiveRoles.length; i++ )
        {
            Role@ role = mActiveRoles[i];
            if( role!=null && role.IsLive() && role.mIsLeft == isLeft )
            {
                if(isLeft)
                {
                    float cur = role.GetRight();
                    if( cur > max )
                    {
                        @result = role;
                        max = cur;
                    }
                }
                else
                {
                    float cur = role.GetLeft();
// Log(formatFloat(max,"",10,2));
// Log(formatFloat(cur,"",10,2));
                    if( cur < max )
                    {
                        @result = role;
                        max = cur;
                    }
                }
            }   
        }

// if(result!=null)
// {
//     Log(formatInt(result.ScriptAdd,"",10));
// }

        return result;
    }
}