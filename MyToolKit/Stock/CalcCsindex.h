#pragma once

class CCalcCsindex : public CCalculateTask
{
public:
	CCalcCsindex(HWND hwnd, int logType);
	~CCalcCsindex(void);

	string ClassName(){ return "CCalcCsindex"; }

	void Execute();
	static void Execute1(void* firstArg);

public:
	vector<string>		m_vec_code			;	//	"公司代码 或者 行业代码",
	vector<string>	m_vec_abbreviation;
	vector<string>	m_vec_trade_date;

	vector<int>		m_vec_is_stock;
	vector<int>		m_vec_company_number;
	vector<double>	m_vec_static_pe;
	vector<double>	m_vec_dynamic_pe;
	vector<double>	m_vec_pb;
	vector<double>	m_vec_dividend_yield_ratio;
};
