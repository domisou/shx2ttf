﻿
// CostEngineerDoc.cpp: CCostEngineerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CostEngineer.h"
#endif

#include "CostEngineerDoc.h"
#include "CntrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCostEngineerDoc

IMPLEMENT_DYNCREATE(CCostEngineerDoc, COleDocument)

BEGIN_MESSAGE_MAP(CCostEngineerDoc, COleDocument)
	// 启用默认的 OLE 容器实现
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleDocument::OnUpdateEditLinksMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, &CCostEngineerDoc::OnUpdateObjectVerbPopup)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CCostEngineerDoc 构造/析构

CCostEngineerDoc::CCostEngineerDoc() noexcept
{
	// 使用 OLE 复合文件
	EnableCompoundFile();

	// TODO: 在此添加一次性构造代码

}

CCostEngineerDoc::~CCostEngineerDoc()
{
}

BOOL CCostEngineerDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCostEngineerDoc 序列化

void CCostEngineerDoc::Serialize(CArchive& ar)
{
	CString str;
	int num;
	double db;
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码

		// 梁
		ar << CString(CBeamObj::m_ObjectCode.c_str());
		ar << CBeamObj::m_ObjectVersion;
		ar << beams.size();
		for (int i = 0; i < beams.size(); i++) {
			beams[i].Serialize(ar, CBeamObj::m_ObjectVersion);
		}

		// 柱
		ar << CString(CColumnObj::m_ObjectCode.c_str());
		ar << CColumnObj::m_ObjectVersion;
		ar << columns.size();
		for (int i = 0; i < columns.size(); i++) {
			columns[i].Serialize(ar, CColumnObj::m_ObjectVersion);
		}

		// 类似工程预算法
		ar << CString(CSimilarEngineerBudget::m_ObjectCode.c_str());
		ar << CSimilarEngineerBudget::m_ObjectVersion;
		ar << similarEngineerBudgets.size();
		for (int i = 0; i < similarEngineerBudgets.size(); i++) {
			similarEngineerBudgets[i].Serialize(ar, CSimilarEngineerBudget::m_ObjectVersion);
		}

		// 概算指标法
		ar << CString(CBudgetIndex::m_ObjectCode.c_str());
		ar << CBudgetIndex::m_ObjectVersion;
		ar << budgetIndexs.size();
		for (int i = 0; i < budgetIndexs.size(); i++) {
			budgetIndexs[i].Serialize(ar, CBudgetIndex::m_ObjectVersion);
		}

		// 施工图预算法
		ar << CString(CBuildingBudget::m_ObjectCode.c_str());
		ar << CBuildingBudget::m_ObjectVersion;
		ar << budgetIndexs.size();
		for (int i = 0; i < buildingBudgets.size(); i++) {
			buildingBudgets[i].Serialize(ar, CBuildingBudget::m_ObjectVersion);
		}

		// 综合单价分析表
		ar << CString(CCompositeUnitPrice::m_ObjectCode.c_str());
		ar << CCompositeUnitPrice::m_ObjectVersion;
		ar << compositeUnitPrices.size();
		for (int i = 0; i < compositeUnitPrices.size(); i++) {
			compositeUnitPrices[i].Serialize(ar, CCompositeUnitPrice::m_ObjectVersion);
		}

		// 文件结束标志
		ar << CString("eof");
	}
	else
	{
		// TODO: 在此添加加载代码

		while (true) {
			ar >> str;
			if (str == "eof") break;
			ar >> db;
			ar >> num;
			for (int i = 0; i < num; i++) {
				// 梁
				if (str == CBeamObj::m_ObjectCode.c_str()) {
					CBeamObj b;
					b.Serialize(ar, db);
					beams.push_back(b);
				}
				// 柱
				if (str == CColumnObj::m_ObjectCode.c_str()) {
					CColumnObj b;
					b.Serialize(ar, db);
					columns.push_back(b);
				}
				// 类似工程预算法
				if (str == CSimilarEngineerBudget::m_ObjectCode.c_str()) {
					CSimilarEngineerBudget b;
					b.Serialize(ar, db);
					similarEngineerBudgets.push_back(b);
				}
				// 概算指标法
				if (str == CBudgetIndex::m_ObjectCode.c_str()) {
					CBudgetIndex b;
					b.Serialize(ar, db);
					budgetIndexs.push_back(b);
				}
				// 施工图预算法
				if (str == CBuildingBudget::m_ObjectCode.c_str()) {
					CBuildingBudget b;
					b.Serialize(ar, db);
					buildingBudgets.push_back(b);
				}
				// 综合单价分析表
				if (str == CCompositeUnitPrice::m_ObjectCode.c_str()) {
					CCompositeUnitPrice b;
					b.Serialize(ar, db);
					compositeUnitPrices.push_back(b);
				}
			}
		}
	}

	// 调用基类 COleDocument 会启用序列化
	//  容器文档的 COleClientItem 对象的序列化。
	COleDocument::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCostEngineerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCostEngineerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCostEngineerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCostEngineerDoc 诊断

#ifdef _DEBUG
void CCostEngineerDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CCostEngineerDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG


// CCostEngineerDoc 命令
