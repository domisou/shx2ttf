#pragma once
#include "basegridctlview.h"

// CAllMainIncomeYearGrowthStockListView 视图

class CAllMainIncomeYearGrowthStockListView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CAllMainIncomeYearGrowthStockListView)

protected:
public:
	CAllMainIncomeYearGrowthStockListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAllMainIncomeYearGrowthStockListView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);
	void Startup();

public:
	virtual void OnInitialUpdate();
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);

private:
	bool	m_bCalculating;
public:
	afx_msg void OnTableAddToSelfSelect();
};


