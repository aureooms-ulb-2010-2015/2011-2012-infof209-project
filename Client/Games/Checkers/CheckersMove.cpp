#include "CheckersMove.hpp"
#include <string>

CheckersMove::CheckersMove(string data){
	this->build(data);
}


CheckersMove::CheckersMove(int rowi,int columni,int rowf,int columnf): _rowi(rowi),_columni(columni),_rowf(rowf),_columnf(columnf){
}
string CheckersMove::serialize(){

	ostringstream temp;
	temp << this->_columni << this->_rowi << this->_columnf << this->_rowf;
	return temp.str();

}

void CheckersMove::build(string data){

	istringstream cs_caster(data.substr(0,1));
	istringstream rs_caster(data.substr(1,1));
	istringstream ce_caster(data.substr(2,1));
	istringstream re_caster(data.substr(3,1));

	cs_caster >> _columni;
	rs_caster >> _rowi;
	ce_caster >> _columnf;
	re_caster >> _rowf;

}

int CheckersMove::row_s(){
	return this->_rowi;
}
int CheckersMove::column_s(){
	return this->_columni;
}
int CheckersMove::row_e(){
	return this->_rowf;
}
int CheckersMove::column_e(){
	return this->_columnf;
}
