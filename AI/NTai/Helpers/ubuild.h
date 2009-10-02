// Universal build.h

namespace ntai {

	class Tunit;

	class CUBuild{
	public:
		CUBuild();
		virtual ~CUBuild();

		bool OkBuildSelection(std::string name);

		/* Initialize object */
		void Init(Global* GL, CUnitTypeData* wu, int uid);

		void SetWater(bool w);

		/* () operator, allows it to be called like this, Object(build); rather than something like object->getbuild(build); */
		std::string operator() (btype build,float3 pos=ZeroVector);
		
		/* metal extractor*/
		std::string GetMEX(); 

		/* energy producer */
		std::string GetPOWER();

		/* random attack unit */
		std::string GetRAND_ASSAULT();
		
		/* most efficient attack unit (give or take a percentage) */
		std::string GetASSAULT();
		
		/* factory */
		std::string GetFACTORY();
		

		/* builders */
		std::string GetBUILDER();
		
		/* geothermal plant */
		std::string GetGEO();
		
		/* scouter */
		std::string GetSCOUT();
		
		/* random unit (no mines) */
		std::string GetRANDOM();
		
		/* random defense */
		std::string GetDEFENCE();
		
		/* radar towers */
		std::string GetRADAR();
		
		/* energy storage */
		std::string GetESTORE();
		
		/* metal storage */
		std::string GetMSTORE();
		
		/* missile silos */
		std::string GetSILO();
		
		/* radar jammers */
		std::string GetJAMMER();
		
		/* sonar */
		std::string GetSONAR();
		
		/* antimissile units */
		std::string GetANTIMISSILE();
		
		/* artillery units */
		std::string GetARTILLERY();
		
		/* focal mines */
		std::string GetFOCAL_MINE();
		
		/* submarines */
		std::string GetSUB();
		
		/* amphibious units (pelican/gimp/triton etc) */
		std::string GetAMPHIB();
		
		/* mines */
		std::string GetMINE();

		/* units with air repair pads that floats */
		std::string GetCARRIER();
		
		/* metal makers */
		std::string GetMETAL_MAKER();
		
		/* walls etc */
		std::string GetFORTIFICATION();
		
		/* Targeting facility type buildings */
		std::string GetTARG();
		
		/* Bomber planes */
		std::string GetBOMBER();
		
		/* units with shields */
		std::string GetSHIELD();
		
		/* units that launch missiles, such as the Merl or diplomat or dominator */
		std::string GetMISSILE_UNIT();
		
		/*  */
		std::string GetFIGHTER();
		
		/*  */
		std::string GetGUNSHIP();
		
		/*  */
		std::string GetHUB();
		
		/*  */
		std::string GetAIRSUPPORT();

		/* To filter out things like dragons eye in AA, things that serve no purpose other than to simply exist */
		bool Useless(CUnitTypeData* u);

	protected:
		
		/*  */
		bool antistall;

		/*  */
		Global* G;

		/*  */
		int uid;

		/*  */
		CUnitTypeData* utd;
		
		/*  */
		bool water;
	};
}
