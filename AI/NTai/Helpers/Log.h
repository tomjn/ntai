#ifndef LOGGER_H
#define LOGGER_H

namespace ntai {

	class Log{
	public:
		Log();
		~Log();

		// << operators
		Log& operator<< (int i);
		Log& operator<< (uint i);
		Log& operator<< (float f);
		Log& operator<< (const char* c);
		Log& operator<< (std::string s);
		Log& operator<< (float3 f);

		TdfParser* startupscript;
		
		std::string FrameTime();						// Returns the Frame Number in the " <xyz Frames> " format
		std::string GameTime();						// Returns Game time in the format "[00:00]" min:sec
		
		void header(std::string message);			// Prints without any game time, used mainly for headers, used for << operators as well
		void print(std::string message);				// Print to log file
		void iprint(std::string message);			// Print to info console and log
		void eprint(std::string message);			// Print an error
		
		void Open(bool plain=false);			// Open Log file
		void Close();							// Close Log file
		void Flush();							// Flushes the log file
		
		void Message(std::string msg,int player);	// Received a message through the console
		
		void Set(Global* GL);

		bool Verbose();
		bool IsVerbose();

		std::map<int,std::string> PlayerNames;			// Player id <> Player name
		bool FirstInstance();					// Is this the first instance of the AI/logger class
	private:
		bool plaintext;
		bool verbose;
		std::ofstream logFile;
		bool First;
		Global* G;
	};
}
#endif
