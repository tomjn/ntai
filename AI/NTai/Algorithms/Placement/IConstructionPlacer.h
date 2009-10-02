
namespace ntai {
	//
	class IConstructionPlacer : public IModule {
	public:
		/**
		 * @brief: 
		 *
		 */
		virtual void operator()()=0;

		/**
		 * @brief: 
		 *
		 */
		virtual void SetTargetUnit(CUnitTypeData* targetunit)=0;
		
		/**
		 * @brief: 
		 *
		 */
		virtual void SetSearchPosition(float3 position)=0;
		
		/**
		 * @brief: 
		 *
		 */
		virtual void SetMaxSearchRadius(float distance)=0;

		/**
		 * @brief: This method starts the search algorithm.
		 * When finished it returns and the final result is 
		 * saved for retrieval via callback. This is a 
		 * blocking method and is made public for those 
		 * circumstances where non-threaded searches are 
		 * required.
		 */
		virtual void StartSearch()=0;

		/**
		 * @brief: 
		 *
		 */
		virtual bool IsSearchFinished()=0;
		
		/**
		 * @brief: 
		 *
		 */
		virtual float3 GetResult()=0;

	};
}
