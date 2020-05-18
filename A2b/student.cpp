#include "student.h"

// Eingabeoperator ">>"
std::istream& operator>>(std::istream& s, Student& a) {
    s >> a.first_name >> a.last_name >> a.matr_nr >> a.grade;
    return s;
}

// Ausgabeoperator "<<"
std::ostream& operator<<(std::ostream& s, const Student& a) {
	s << a.first_name << " " << a.last_name << " " << a.matr_nr << " " << a.grade;
	return s;
}

// Vergleichsoperator "<"
bool operator<(const Student& a, const Student& b) {
	if (a.last_name < b.last_name)
	{
		return true;
	}

	else if (a.last_name == b.last_name)
	{
		return (a.first_name < b.first_name);
	
	}
}

// Vergleichsoperatoren "==" bzw. "!="
bool operator==(const Student& a, const Student& b) {
	return (a.last_name == b.last_name && a.first_name == b.first_name && a.matr_nr == b.matr_nr);
	
}

bool operator!=(const Student& a, const Student& b) {
	return (a.last_name != b.last_name || a.first_name != b.first_name || a.matr_nr != b.matr_nr);
	
	
}
