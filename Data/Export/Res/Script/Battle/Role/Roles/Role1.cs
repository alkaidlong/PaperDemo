#include "Role.cs"
#include "RoleSkill.cs"

class Role1 : Role
{
    Role1()
    {
         IconName = "JarvenIVIcon.png";
         StarCount = 1;

         WalkName = "JarvenIVWalk.ani";
         RunName = "JarvenIVRun.ani";
//          Attack1Name = "JarvenIVAttack.ani";
//          Attack2Name = "JarvenIVAttack.ani";
//          Attack3Name = "JarvenIVAttack.ani";
//          Attack4Name = "JarvenIVAttack.ani";
//          Attack5Name = "JarvenIVAttack.ani";
         IdleName = "JarvenIVIdle.ani";
         RestName = "";
         WinName = "JarvenIVVictory.ani";
         HitName = "JarvenIVHitInterrupt.ani";
         HitDownName = "JarvenIVKnockedDown.ani";
         HitBackName = "JarvenIVWereRepulsed.ani";
         WaitName = "";
         DeadName = "JarvenIVDeath.ani";

         PropertyID = 1;
	     PropertyLevel = 1;

//        StandDistanceToTarget = 200.0f;
        RoleWidth = 164.0f;
        RoleHeight = 120.0f;
        RoleXOffset = -82.0f;
        RoleYOffset = 0.0f;

         RoleSkill@ skill1 = RoleSkill(); //ÆÕÍ¨¹¥»÷
         skill1.RoleSkillActionName = "JarvenIVAttack.ani";
         skill1.SkillTirggerIndex = 6;
         skill1.SkillIconName = "JarvenIVIcon.png";
         skill1.SkillDataID = 1;
         skill1.SkillLogicID = 1;
         skill1.SkillLevel = 1;
         skill1.CoolDown = 0.0f;
         skill1.EnergyConsumption = 100.0f;
         skill1.AttackDistance = 100.0f;
         skill1.ShowColorID = 0;
         mSkills.insertLast(skill1);

        RoleSkill@ skill2 = RoleSkill();
        skill2.RoleSkillActionName = "JarvenIVAttack.ani";
        skill2.SkillTirggerIndex = 6;
        skill2.SkillIconName = "JarvenIVIcon.png";
        skill2.SkillDataID = 2;
        skill2.SkillLogicID = 2;
        skill2.SkillLevel = 4;
        skill2.CoolDown = 15.0f;
        skill2.EnergyConsumption = 80.0f;
        skill2.AttackDistance = 130.0f;
        skill2.ShowColorID = 0;
        mSkills.insertLast(skill2);

//         RoleSkill@ skill3 = RoleSkill();
//         skill3.RoleSkillActionName = "JarvenIVAttack.ani";
//         skill3.SkillTirggerIndex = 6;
//         skill3.SkillIconName = "";
//         skill3.SkillDataID = 1;
//         skill3.SkillLogicID = 1;
//         skill3.CoolDown = 100.0f;
//         skill3.EnergyConsumption = 100.0f;
//         skill3.AttackDistance = 100.0f;
//         skill3.ShowColorID = 0;
//         mSkills.insertLast(skill3);
// 
//         RoleSkill@ skill4 = RoleSkill();
//         skill4.RoleSkillActionName = "JarvenIVAttack.ani";
//         skill4.SkillTirggerIndex = 6;
//         skill4.SkillIconName = "";
//         skill4.SkillDataID = 1;
//         skill4.SkillLogicID = 1;
//         skill4.SkillLevel = 1;
//         skill4.CoolDown = 100.0f;
//         skill4.EnergyConsumption = 100.0f;
//         skill4.AttackDistance = 100.0f;
//         skill4.ShowColorID = 0;
//         mSkills.insertLast(skill4);
// 
//         RoleSkill@ skill5 = RoleSkill();
//         skill5.RoleSkillActionName = "JarvenIVAttack.ani";
//         skill5.SkillTirggerIndex = 6;
//         skill5.SkillIconName = "";
//         skill5.SkillDataID = 1;
//         skill5.SkillLogicID = 1;
//         skill5.SkillLevel = 1;
//         skill5.CoolDown = 100.0f;
//         skill5.EnergyConsumption = 100.0f;
//         skill5.AttackDistance = 100.0f;
//         skill5.ShowColorID = 0;
//         mSkills.insertLast(skill5);
// 
//         RoleSkill@ skill6 = RoleSkill();
//         skill6.RoleSkillActionName = "JarvenIVAttack.ani";
//         skill6.SkillTirggerIndex = 6;
//         skill6.SkillIconName = "";
//         skill6.SkillDataID = 1;
//         skill6.SkillLogicID = 1;
//         skill6.SkillLevel = 1;
//         skill6.CoolDown = 100.0f;
//         skill6.EnergyConsumption = 100.0f;
//         skill6.AttackDistance = 100.0f;
//         skill6.ShowColorID = 0;
//         mSkills.insertLast(skill6);

        mSkillsSequence.insertLast(0);
        mSkillsSequence.insertLast(0);
        mSkillsSequence.insertLast(1);
    }

    ~Role1()
    {

    }

}