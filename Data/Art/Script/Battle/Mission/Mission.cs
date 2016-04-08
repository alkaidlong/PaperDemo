#include "Role.cs"
#include "Common.cs"

class Mission
{
    float DefaultRoleWidth = 100.0f;
    float BGMoveTime = 0.0f;//±³¾°ÒÆ¶¯Ê±¼ä
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

    array<Role@> mLeftRolses;
    array<Role@> mRightRoles;

    float mTime = 0.0f;
    bool mTemp = false;

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
//         if(IsLeftMove)
//         {
//             for(uint i = 0;i<mLeftRolses.length;i++)
//             {
//                  Role @roleRef = mLeftRolses[i];
//                  roleRef.Initialize();
// //                  if(roleRef.mTeam == Game::RoleType::Player)
// //                  {
// //                     roleRef.SetPosition((5-roleRef.mPlayerRoleIndex)*100.0f,0);
// //                  }
//             }
//         }
//         else
//         {
//             for(uint i = 0;i<mRightRoles.length;i++)
//             {
//                  Role @roleRef = mRightRoles[i];
//                  roleRef.Initialize();
//                  //TODO
//             }
//         }

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

    void IntoBattle()
    {
        for(uint i = 0;i<mLeftRolses.length;i++)
        {
             Role @roleRef = mLeftRolses[i];
             roleRef.IntoBattle();
        }

        for(uint i = 0;i<mRightRoles.length;i++)
        {
             Role @roleRef = mRightRoles[i];
             roleRef.IntoBattle();
        }
    }

    void Uninitialize() 
    {
        
    }

    void AddRole(int roleScriptAdd,int index)
    {
         Role @roleRef = cast<Role>(Game::GetScriptHandle(roleScriptAdd));
         roleRef.mPlayerRoleIndex = index;
         switch(roleRef.mTeam)
         {
         case Game::RoleType::Player:
         case Game::RoleType::NPC:
              roleRef.mIsLeft = IsLeftMove;
              roleRef.mIsLeftTeam = IsLeftMove;
              break;
         case Game::RoleType::Monster:
         case Game::RoleType::Boss:
              roleRef.mIsLeft = !IsLeftMove;
              roleRef.mIsLeftTeam = !IsLeftMove;
              break;
         }
         roleRef.Initialize();
         if(IsLeftMove)
         {
            if( roleRef.mIsLeftTeam )
            {
                if( mLeftRolses.length > 0 )
                {
                   Role @lastRole = mLeftRolses[mLeftRolses.length-1];
                   float tempDefaultRoleWidth = 0.0f;
                   if(roleRef.mPlayerRoleIndex>=0 && lastRole.mPlayerRoleIndex>=0)
                   {
                        tempDefaultRoleWidth = (roleRef.mPlayerRoleIndex - lastRole.mPlayerRoleIndex - 1)*DefaultRoleWidth;
                   }
                   roleRef.SetPosition(lastRole.GetLeft() - roleRef.RoleXOffset - roleRef.RoleWidth - roleRef.RoleSpacingMin - tempDefaultRoleWidth,0);
                }
                mLeftRolses.insertLast(roleRef);
            }
            else
            {
                if( mRightRoles.length > 0 )
                {
                   Role @lastRole = mRightRoles[mRightRoles.length-1];
                   roleRef.SetPosition(lastRole.GetRight() + roleRef.RoleXOffset + roleRef.RoleWidth + roleRef.RoleSpacingMin,0);
                }
                mRightRoles.insertLast(roleRef);
            }
         }
         else
         { 
            if( !roleRef.mIsLeftTeam )
            {
                if( mRightRoles.length > 0 )
                {
                   Role @lastRole = mRightRoles[mRightRoles.length-1];
                   float tempDefaultRoleWidth = 0.0f;
                   if(roleRef.mPlayerRoleIndex>=0 && lastRole.mPlayerRoleIndex>=0)
                   {
                        tempDefaultRoleWidth = (roleRef.mPlayerRoleIndex - lastRole.mPlayerRoleIndex - 1)*DefaultRoleWidth;
                   }
                   tempDefaultRoleWidth = roleRef.mPlayerRoleIndex - lastRole.mPlayerRoleIndex;
                   roleRef.SetPosition(lastRole.GetRight() + roleRef.RoleXOffset + roleRef.RoleWidth + roleRef.RoleSpacingMin + tempDefaultRoleWidth,0);
                }
                mRightRoles.insertLast(roleRef);
            }
            else
            {
                if( mLeftRolses.length > 0 )
                {
                   Role @lastRole = mLeftRolses[mLeftRolses.length-1];
                   roleRef.SetPosition(lastRole.GetLeft() - roleRef.RoleXOffset - roleRef.RoleWidth - roleRef.RoleSpacingMin,0);
                }
                mLeftRolses.insertLast(roleRef);
            }
         }
    }

    void WaitForMe()
    {
   
    }

//     void OverRole( Role @roleRef )
//     {
//         int index = mActiveRoles.find(roleRef);
//         if( index != -1)
//         {
//             mActiveRoles.removeAt(index);
//         }
//     }

    void UpdateRoles(float dt)
    {
        for(uint i = 0;i<mLeftRolses.length;i++)
        {
            Role@ role = mLeftRolses[i];
            if( i == 0 )
            {
                if(mTime>10.0f &&!mTemp)
                {
                    mTemp = true;
                    role.SetPosition(999,0);
                }
                role.Update(dt,null);
            }
            else
            {
                role.Update(dt,mLeftRolses[i-1]);
            }
        }

        for(uint i = 0;i<mRightRoles.length;i++)
        {
            Role@ role = mRightRoles[i];
            if( i == 0 )
            {
                role.Update(dt,null);
            }
            else
            {
                role.Update(dt,mRightRoles[i-1]);
            }
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
                if(roleRef.mAction == RoleAction::Rest)
                {
                    if( roleRef.mX - Game::GetSceneWidth()/2.0f < 0.0f )
                    {
                        roleRef.SetAction(RoleAction::Walk);
                    }
                     mCamerSpeed = -mSceneWidth/BGMoveTime;
                }
                else
                {
                    if( Game::GetSceneWidth()/2.0f - roleRef.mX < -100.0f )
                    {
                        roleRef.SetAction(RoleAction::Rest);
                        mCamerSpeed = -mSceneWidth/BGMoveTime;
                    }
                    else if( Game::GetSceneWidth()/2.0f - roleRef.mX < -1.0f )
                    {
                        if(-mCameraPositionX<mSceneWidth)
                        {
                            if( roleRef.mAction == RoleAction::Walk )
                            {
                                mCamerSpeed = -roleRef.WalkMoveSpeed;
                            }
                            else if(roleRef.mAction == RoleAction::Run)
                            {
                                mCamerSpeed = -roleRef.RunMoveSpeed;
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
            }
            else
            {
//                 if(Game::GetSceneWidth()/2.0f - roleRef.mX > 1.0f)
//                 {
//                     if( roleRef.mAction == RoleAction::Walk )
//                     {
//                         mCamerSpeed = roleRef.WalkMoveSpeed;
//                     }
//                     else if(roleRef.mAction == RoleAction::Run)
//                     {
//                         mCamerSpeed = roleRef.RunMoveSpeed;
//                     }
//                     else
//                     {
//                         mCamerSpeed = mSceneWidth/BGMoveTime;
//                     }
//                 }
//                 else if( Game::GetSceneWidth()/2.0f - roleRef.mX > 100.0f )
//                 {
//                     roleRef.SetAction(RoleAction::Rest);
//                     mCamerSpeed = mSceneWidth/BGMoveTime;
//                 }
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
        UpdateRoles(dt);
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

        if(isLeft)
        {
            for( uint i = 0 ; i<mLeftRolses.length; i++ )
            {
                Role@ role = mLeftRolses[i];
                if( role!=null && role.IsLive())
                {
                    float cur = role.GetRight();
                    if( cur > max )
                    {
                        @result = role;
                        max = cur;
                    }
                }
            }
        }
        else
        {
            for( uint i = 0 ; i<mRightRoles.length; i++ )
            {
                Role@ role = mRightRoles[i];
                if( role!=null && role.IsLive())
                {
                    float cur = role.GetLeft();
                    if( cur < max )
                    {
                        @result = role;
                        max = cur;
                    }
                }

            }
        }
        return result;
// Log(formatFloat(max,"",10,2));
// Log(formatFloat(cur,"",10,2));
// Log(formatInt(result.ScriptAdd,"",10));

    }
}