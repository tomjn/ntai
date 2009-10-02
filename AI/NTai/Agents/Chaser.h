#ifndef CHASER_H
#define CHASER_H

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// The chaser class, deals with attacking and defending.

namespace ntai {
	class Chaser{
	public:
		Chaser();
		virtual ~Chaser();
		void InitAI(Global* GLI);
		void Add(int unit,bool aircraft=false);
		void Beacon(float3 pos, float radius);
		void UnitDestroyed(int unit,int attacker);
		void UnitFinished(int unit);
		void EnemyDestroyed(int enemy, int attacker);
		bool FindTarget(std::set<int> atkgroup, bool upthresh=true);
		void UnitDamaged(int damaged,int attacker,float damage,float3 dir);
		void UnitIdle(int unit);

		void Update();
		void FireSilos();
		void MakeTGA();
		void UpdateMatrixFriendlyUnits();
		void UpdateMatrixEnemies();

		void DoUnitStuff(int aa);
		std::set<int> engaged;
		std::set<int> walking;

		int threshold;
		float thresh_increase;
		float thresh_percentage_incr;
		int max_threshold;
		std::set<int> Attackers;
		std::set<int> sweap;

		float3 swtarget;


		Global* G;

		/**
		 * used for storing attackers while forming a group
		 */
		std::set<int> temp_attack_units;

		/**
		 * used for storing air attackers while forming a group
		 */
		std::set<int> temp_air_attack_units;
		
		std::vector<std::set<int> > attack_groups;
		std::vector<std::set<int> > air_attack_groups;

		/**
		 * a set of attackers that have been finished, but are still leaving the factory
		 */
		std::set<int> unit_to_initialize;	
		
		int enemynum;
		std::vector<std::string> hold_pos;
		std::vector<std::string> maneouvre;
		std::vector<std::string> roam;
		std::vector<std::string> hold_fire;
		std::vector<std::string> return_fire;
		std::vector<std::string> fire_at_will;

		CGridManager Grid;

	};
}
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
#endif

