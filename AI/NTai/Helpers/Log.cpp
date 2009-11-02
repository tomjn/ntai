#include "../Core/include.h"

namespace ntai {
	int Lmagic;

	Log::Log() : G(NULL) {
		verbose = false;
		First = false;
	}

	Log::~Log(){
		G = 0;
	}

	void Log::Set(Global* GL){
		G = GL;
		if(GL ==0){
			int jk = 3;
		}
		if(G ==0){
			int jk = 3;
		}
	}

	std::string Log::FrameTime(){
		return " < Frame: " + to_string(G->cb->GetCurrentFrame()) + " >";
	}

	std::string Log::GameTime(){
		int Time = G->cb->GetCurrentFrame();
		Time = Time/30;
		int Seconds = Time%60;
		int Minutes = (Time/60)%60;
		int hours = 0;
		if(Time>3600) hours = (Time-(Time%3600))/3600;
		if(Seconds+Minutes+hours == 0){
			return "[-]";
		}
		std::string stime="[";
		if(hours>0){
			if(hours<10) stime += "0";
			stime += to_string(hours);
			stime += ":";
		}
		if(Minutes<10){
			stime += "0";
		}
		stime += to_string(Minutes);
		stime += ":";
		if(Seconds <10){
			stime += "0";
		}
		stime += to_string(Seconds);
		stime += "]";

		return stime;
	}

	bool Log::FirstInstance(){
		return First;
	}

	std::string GetSysTime(){
		time_t now1;
		time(&now1);//struct
		tm *now2;
		now2 = localtime(&now1);
		std::string s = std::string("|")+to_string(now2->tm_hour)+ std::string(":")+ to_string(now2->tm_min)+std::string(":")+ to_string(now2->tm_sec)+std::string("|");
		return s;
	}

	void Log::Open(){
		//char buffer[1000];
		if( Lmagic != 95768){
			Lmagic = 95768;
			First = true;
		}


		time_t now1;
		time(&now1);
		struct tm *now2;
		now2 = localtime(&now1);
		std::string filename = G->info->datapath + slash + "Logs" + slash;

		// DDD MMM DD HH:MM:SS YYYY_X - NTAI.log
		filename += to_string(now2->tm_mon+1)+"-" +to_string(now2->tm_mday) + "-" +to_string(now2->tm_year + 1900) +"-" +to_string(now2->tm_hour) +"_" +to_string(now2->tm_min) +"["+to_string(G->Cached->team)+"]XE10.1.log";

		logFile.open(filename.c_str());
		if(logFile.is_open() == false){
			logFile.close();
			logFile.open(filename.c_str());
			if(logFile.is_open() == false){
				iprint(std::string("Error!!! ") + filename + std::string(" refused to open!"));
				verbose = true;
				return;
			}
		}

		header(" :: NTAI XE10.1 Log File \n :: Programmed and maintained by AF/T.Nowell \n :: Copyright (C) 2004 Tom Nowell/AF \n");
		logFile << " :: Game started: " << now2->tm_mday << "." << now2->tm_mon << "." << 1900 + now2->tm_year << "  " << now2->tm_hour << ":" << now2->tm_min << ":" << now2->tm_sec << std::endl << std::endl <<  std::flush;
		
		
		int size = G->cb->GetFileSize("modinfo.tdf");
		char* c = new char[size];
		if(size > 0){
			G->cb->ReadFile(filename.c_str(),c,size);
			
			TdfParser cp;
			cp.LoadBuffer(c,(std::size_t)size);
			
			std::string tempstr = "";
			cp.SGetValue(tempstr, "MOD\\Name");
			logFile << " :: " << tempstr << std::endl <<  std::flush;
			
			tempstr = "";
			cp.SGetValue(tempstr, "MOD\\Description");
			logFile << " :: " << tempstr << std::endl <<  std::flush;
		}

		if(First == true) logFile << " :: First instance of NTAI" << std::endl;
		
		logFile << std::endl <<  std::flush;
	}

	void Log::print(std::string message){
		if(message.empty() == true) return;
		if (!G) {
			//NLOG(message);
			return;
		}
		std::string gtime;
		gtime = GameTime() + GetSysTime() +FrameTime() + message + "\n";
		header(gtime);
	}

	void Log::header(std::string message){
		if(message.empty() == true) return;
		if(verbose){
			G->cb->SendTextMsg(message.c_str(), 1);
		}
		std::string gtime="";
		gtime = message;
		if (logFile.is_open()){
#ifdef TNLOG
			std::cout << gtime << std::endl << std::flush;
#endif
			logFile << gtime << std::flush;
		}
	}

	void Log::iprint(std::string message){
		std::string gtime = GameTime() + message;
		G->cb->SendTextMsg(gtime.c_str(), 1);
		print(message);
	}

	void Log::Close(){
		if(logFile.is_open()){
			header(" :: Closing LogFile...\n");
			logFile.close();
		}
	}

	void Log::Flush(){
		if(logFile.is_open() == true){
			logFile.flush();
		}
	}

	void Log::Message(std::string msg, int player){
		std::string m = "[" + PlayerNames[player] + "] " + GameTime() + FrameTime() +  " :: " + msg + "\n";
		header(m);
		return;
	}

	void Log::eprint(std::string message){
		if(G){
			G->cb->SendTextMsg(message.c_str(), 3);
		}
		print(message);
	}

	Log& Log::operator<< (const char* c){
		this->header(c);
		return *this;
	}

	Log& Log::operator<< (std::string s){
		this->header(s);
		return *this;
	}

	Log& Log::operator<< (int i){
		std::string s = to_string(i);
		header(s);
		return *this;
	}
	Log& Log::operator<< (uint i){
		std::string s = to_string(i);
		header(s);
		return *this;
	}

	Log& Log::operator<< (float f){
		header(to_string(f));
		return *this;
	}

	Log& Log::operator<< (float3 f){
		header(to_string(f.x)+","+to_string(f.y)+","+to_string(f.z));
		return *this;
	}

	bool Log::Verbose(){
		if(verbose == true){
			verbose = false;
		}else{
			verbose = true;
		}
		return verbose;
	}

	bool Log::IsVerbose(){
		return verbose;
	}
}
