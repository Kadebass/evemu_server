#ifndef __COMMANDDISPATCHER_H_INCL__
#define __COMMANDDISPATCHER_H_INCL__

#include "../common/types.h"
#include <string>
#include <map>

#include "admin/CommandDB.h"

class Client;
class Seperator;
class PyResult;
class PyServiceMgr;

class CommandDispatcher {
public:
	//this is the prototype for a command function:
	typedef PyResult (*CommandFunc)(Client *who, CommandDB *db, PyServiceMgr *services, const Seperator &args);
	
	class CommandRecord {
	public:
		std::string command;
		std::string description;
		uint32 required_role;
		CommandFunc function;
	};

	CommandDispatcher(PyServiceMgr &services, DBcore &db);
	virtual ~CommandDispatcher();

	PyResult Execute(Client *from, const char *msg);

	void AddCommand(const char *cmd, const char *desc, uint32 required_role, CommandFunc function);
	
protected:
	PyServiceMgr &m_services;
	CommandDB m_db;
	
	std::map<std::string, CommandRecord *> m_commands;	//we own these pointers
};







#endif

