#include "sort.h"

bool sortByNameUp(outlet o, outlet o2) { //d,c,b,a
	return o.getName() < o2.getName();
}
bool sortByNameDown(outlet o, outlet o2) { //a,b,c,d
	return o.getName() > o2.getName();
}
bool sortByAbilityUp(outlet o, outlet o2) {
	return o.abilityToTrade() < o2.abilityToTrade();
}
bool sortByAbilityDown(outlet o, outlet o2) {
	return o.abilityToTrade() > o2.abilityToTrade();
}
bool sortByPermissionsUp(outlet o, outlet o2) {
	return o.getPermissionsSum() < o2.getPermissionsSum();
}
bool sortByPermissionsDown(outlet o, outlet o2) {
	return o.getPermissionsSum() > o2.getPermissionsSum();
}
