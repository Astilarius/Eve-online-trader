#pragma once

class System
{
public:
	System();
	System(const System& other);
	System(System&& other);
	System& operator=(const System& other);
	System& operator=(System&& other);
	friend std::ostream& operator<<(std::ostream& os, System& dt);

	int system_id;
	std::string system_name;
	double security_status;
};

System::System()
{
	this->system_id = 0;
	this->system_name = "";
	this->security_status = 0;
}

System::System(const System& other)
{
	this->system_id = other.system_id;
	this->system_name = other.system_name;
	this->security_status = other.security_status;
}

System::System(System&& other)
{
	this->system_id = other.system_id;
	this->system_name = other.system_name;
	this->security_status = other.security_status;

	other.system_id = 0;
	other.system_name = "";
	other.security_status = 0;
}

System& System::operator=(const System& other)
{
	this->system_id = other.system_id;
	this->system_name = other.system_name;
	this->security_status = other.security_status;
	return *this;
}

System& System::operator=(System&& other)
{
	if (this != &other)
	{
		this->system_id = 0;
		this->system_name = "";
		this->security_status = 0;

		this->system_id = other.system_id;
		this->system_name = other.system_name;
		this->security_status = other.security_status;

		other.system_id = 0;
		other.system_name = "";
		other.security_status = 0;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, System& dt)
{
	os << "system_id: " << dt.system_id << '\n';
	os << "system_name: " << dt.system_name << '\n';
	os << "security_status: " << dt.security_status << '\n';
	return os;
}