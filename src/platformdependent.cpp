#include <process.h>
#include <processes.h>

#include <experimental/filesystem>
#include <fstream>
#include <string.h>
#include <sstream>




/*=============================== Processes functions ===============================*/
bool IsNumerical(const std::string& path){
	bool result = true;
	for(unsigned int c=6; c<path.size(); ++c){
		if(path[c]<'0' || path[c]>'9'){
			result = false;
			break;
		}
	}
	return result;
}
#include <iostream>
void Processes::GetProcesses(){
	for(const auto& entry : std::experimental::filesystem::directory_iterator("/proc/")){
		const std::string& _path = entry.path();
		std::string path(_path.begin(), _path.end());
		if(IsNumerical(path) && std::experimental::filesystem::is_directory(path)){
			for(const auto& entry2 : std::experimental::filesystem::directory_iterator(path)){
				const std::string& __path = entry2.path();
				std::string path2(__path.begin(), __path.end());
				if(strcmp(path2.c_str()+path2.size()-5, "/stat")==0){
					std::cout<<path2<<" : ";
					std::ifstream ifs(path2);
					std::string line = "";
					std::getline(ifs, line);
					std::cout<<line<<"\n";
					ifs.close();
					processes.push_back(Process(line));
				}
				//std::string line = "";
				//while(std::getline(ifs, line)){
				//	std::cout<<line<<"\n";
				//}
				//ifs.close();
			}
		}
	}
	//processes.push_back(Process("proc/100"));
}


void Processes::GenerateMemoryProfile(Process* process){
	
}


void Processes::GenerateCPUProfile(Process* process){
	/*get number of threads*/

}


void Processes::GenerateOpenFileProfile(Process*){

}


void Processes::GenerateOpenPortProfile(Process* process){

}



/*=============================== Process functions ===============================*/
Process::Process(const std::string& proc_stat_str): status(0x0){

	/*
		pid
		name
		state
		ppid
		pgroup
		session
		controlling terminal
		foreground process group of terminal
		kernel flags
		minflt
		cminflt
		number of major faults
		(52 fields in total...)
	*/

  /*parse proc stat string into various fields*/
  std::stringstream ss(proc_stat_str);
  unsigned int pid = 0; ss >> pid;
  std::string proc_name = ""; ss >> proc_name;
  unsigned char state = 0; ss >> state;
  long long other_fields[52];
  for(unsigned int i=3; i<52; ++i){
    ss>>other_fields[i];
  }

	//get process ID
	process_ID = pid;

	//get process name
	process_name = proc_name;

  //gen profiles
  memp.SetProfile(other_fields[9], other_fields[11], other_fields[22], other_fields[23], other_fields[35]);
  cpup.SetProfile(other_fields[13], other_fields[14], other_fields[18], other_fields[19], other_fields[38]);
}


void Process::CleanUp(){

}
