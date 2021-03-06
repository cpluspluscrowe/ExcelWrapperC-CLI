#include "stdafx.h"
#include "Workbook.h"
#include "ExcelApplication.h"
#include "Worksheet.h"

///Workbook functions
ExcelApplicationWrapper::Workbook::Workbook(Excel::Application^ xl, System::String^ filePath)
{
	this->wrappedWorkbook = xl->Workbooks->Open(filePath, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing);
	this->Sheets = gcnew ExcelApplicationWrapper::WorkbookSheetsWrapper(this->wrappedWorkbook);
	this->Name = this->wrappedWorkbook->Name;
}
ExcelApplicationWrapper::Workbook::Workbook(Excel::Workbook^ wb){
	this->wrappedWorkbook = wb;
	this->Sheets = gcnew ExcelApplicationWrapper::WorkbookSheetsWrapper(this->wrappedWorkbook);
	this->Name = this->wrappedWorkbook->Name;
}

ExcelApplicationWrapper::Workbook::!Workbook(){
}

ExcelApplicationWrapper::Workbook::~Workbook(){
}
Excel::Workbook^ ExcelApplicationWrapper::Workbook::GetWrappedWorkbook(){
	return this->wrappedWorkbook;
}


///Sheets Wrapper functions
ExcelApplicationWrapper::WorkbookSheetsWrapper::WorkbookSheetsWrapper(Excel::Workbook^ workbook){
	this->wrappedWorkbook = workbook;
}

ExcelApplicationWrapper::Worksheet^ ExcelApplicationWrapper::WorkbookSheetsWrapper::operator [](String^ worksheetName){
	return static_cast<ExcelApplicationWrapper::Worksheet^>(gcnew ExcelApplicationWrapper::Worksheet(static_cast<Excel::Worksheet^>(this->wrappedWorkbook->Sheets[worksheetName])));
}
ExcelApplicationWrapper::Worksheet^ ExcelApplicationWrapper::WorkbookSheetsWrapper::operator [](int worksheetNumber){
	return static_cast<ExcelApplicationWrapper::Worksheet^>(gcnew ExcelApplicationWrapper::Worksheet(static_cast<Excel::Worksheet^>(this->wrappedWorkbook->Sheets[worksheetNumber])));
}
bool ExcelApplicationWrapper::Workbook::Save(){
	try{
		this->wrappedWorkbook->Save();
		return true;
	}
	catch (const int& e){
		throw std::exception("Failed to save");
	}
	return false;
}
bool ExcelApplicationWrapper::Workbook::Close(bool saveIt){
	try{
		this->wrappedWorkbook->Close((System::Object^)saveIt, Type::Missing, Type::Missing);
		return true;
	}
	catch (const int& e){
		throw std::exception("Failed to close");
	}
	return false;
}

ExcelApplicationWrapper::Worksheet^ ExcelApplicationWrapper::WorkbookSheetsWrapper::Add(){
	ExcelApplicationWrapper::Worksheet^ ws = gcnew Worksheet(static_cast<Excel::Worksheet^>(this->wrappedWorkbook->Sheets->Add((System::Object^)Type::Missing, (System::Object^)Type::Missing, (System::Object^)Type::Missing, (System::Object^)Type::Missing)));
	return ws;
}