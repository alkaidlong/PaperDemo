#include "Role.cs"

class Role20001 : Role
{
    Role20001()
    {
         IconName = "PantheonIcon.png";
         StarCount = 1;

         WalkName = "PantheonWalk.ani";
         RunName = "PantheonRun.ani";
//          Attack1Name = "PantheonAttack.ani";
//          Attack2Name = "PantheonAttack.ani";
//          Attack3Name = "PantheonAttack.ani";
//          Attack4Name = "PantheonAttack.ani";
//          Attack5Name = "PantheonAttack.ani";
         IdleName = "PantheonIdle.ani";
         RestName = "";
         WinName = "PantheonVictory.ani";
         HitName = "PantheonHitInterrupt.ani";
         HitDownName = "PantheonKnockedDown.ani";
         HitBackName = "PantheonWereRepulsed.ani";
         WaitName = "";
         DeadName = "PantheonDeath.ani";

         PropertyID = 3;
	     PropertyLevel = 3;
    }

    ~Role20001()
    {

    }

}