#include "StdAfx.h"
#include "Lottery.h"
#include "LotteryDoc.h"
#include "CSVFile.h"
#include "CalcLotteryNumberEnum.h"

CCalcLotteryNumberEnum::CCalcLotteryNumberEnum(HWND hwnd, int logType)
:CCalculateTask(hwnd, logType)
{
	m_max_1 = m_max_2 = m_max_3 = m_max_4 = m_max_5 = 0;
}

CCalcLotteryNumberEnum::~CCalcLotteryNumberEnum(void)
{
}



string CCalcLotteryNumberEnum::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists lottery_" << m_lottery_doc.m_lottery_info.code
		<< "( name varchar(32), "
		<< " number_1 int, number_2 int,number_3 int, number_4 int, number_5 int, number_6 int, number_7 int, "
		<< " special_number int, "
		<< " sum_number int, odd int ,even int , equal_tail varchar(32), "
		<< " consecutive0 varchar(32),  consecutive1 varchar(32),  consecutive2 varchar(32),"
		<< " var decimal(8,2), stdev decimal(8,2), devsq decimal(8,2), kurt decimal(8,2), skew decimal(8,2), "
		<< " ac int, group_qty int, fringe_no_qty int, fred decimal(8,2), "
		<< " interval_12 int, interval_23 int, interval_34 int, interval_45 int, interval_56 int, interval_67 int, ";
	if (m_lottery_doc.m_lottery_info.specialnum)
	{
		ss << " sum_number_s int, odd_s int ,even_s int , equal_tail_s varchar(32), "
			<< " consecutive0_s varchar(32),  consecutive1_s varchar(32),  consecutive2_s varchar(32),"
			<< " var_s decimal(8,2), stdev_s decimal(8,2), devsq_s decimal(8,2), kurt_s decimal(8,2), skew_s decimal(8,2), "
			<< " ac_s int, group_qty_s int, fringe_no_qty_s int, fred_s decimal(8,2), "
			<< " interval_12_s int, interval_23_s int, interval_34_s int, interval_45_s int, " 
			<< " interval_56_s int, interval_67_s int, interval_78_s int, special_first int,";
	}
	ss	<< " PRIMARY KEY ( number_1, number_2, number_3, number_4, number_5 ";
	if (m_lottery_doc.m_lottery_info.regularnum > 5)	ss << ", number_6 ";
	if (m_lottery_doc.m_lottery_info.regularnum > 6)	ss << ", number_7 ";
	if (m_lottery_doc.m_lottery_info.specialnum > 0)	ss << ", special_number ";
	ss << " ))";
	return ss.str();
}

void CCalcLotteryNumberEnum::EnumSpecialNumber(LotteryNumber  lo)
{
	bool bInsert = false;
	if (lo.number[0] > m_max_1)
		bInsert = true;
	else if (lo.number[0] < m_max_1)
		bInsert = false;
	else if (lo.number[1] > m_max_2)
		bInsert = true;
	else if (lo.number[1] < m_max_2)
		bInsert = false;
	else if (lo.number[2] > m_max_3)
		bInsert = true;
	else if (lo.number[2] < m_max_3)
		bInsert = false;
	else if (lo.number[3] > m_max_4)
		bInsert = true;
	else if (lo.number[3] < m_max_4)
		bInsert = false;
	else if (lo.number[4] > m_max_5)
		bInsert = true;
	else if (lo.number[4] < m_max_5)
		bInsert = false;
	else
		bInsert = true;

	if (bInsert)
	{
		if (m_lottery_doc.m_lottery_info.specialnum > 0)
		{
			int special_first = 1;
			for (int k = 1; k <= m_lottery_doc.m_lottery_info.totalnum; k++)
			{
				bool bFound = false;
				for (int m = 0; m < m_lottery_doc.m_lottery_info.regularnum; m++)
				{
					if (lo.number[m] == k)
					{
						bFound = true;
						break;
					}
				}
				if (bFound == false)
				{
					if (special_first)
					{
						special_first = 0;
						lo.special_first = 1;
					}
					else
						lo.special_first = 0;

					lo.special_number = k;
					m_vec_lottery_number.push_back(lo);
				}
			}
		}
		else
		{
			m_vec_lottery_number.push_back(lo);
		}

		//	ÿ�� 10 W ������һ�����ݿ�
		if (m_vec_lottery_number.size() > 10 * 10000)
		{
			ImportToDatabase();
			m_vec_lottery_number.clear();
		}
	}

}

void CCalcLotteryNumberEnum::Execute1(void* firstArg)
{
	CCalcLotteryNumberEnum * sink = (CCalcLotteryNumberEnum *)firstArg;
	sink->Execute();
}


void CCalcLotteryNumberEnum::ImportToDatabase(void)
{
	stringstream ss;
	
	//	���ȱ�����ʱ�ļ�
	char buffer[64] = { 0 };
	GUID guid;
	if (CoCreateGuid(&guid))
	{
		AfxMessageBox("create guid error");
		return ;
	}
	sprintf_s(buffer, sizeof(buffer),
		"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X.dat",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);

	
	try
	{
		LotteryNumber ln;
		ofstream outfile(buffer, ofstream::out);
		for (int row = 0; row < m_vec_lottery_number.size(); row++)
		{
			ss.str("");
			ss << "\"" << m_lottery_doc.m_lottery_info.name << "\""
				<< "," << m_vec_lottery_number[row].number[0]
				<< "," << m_vec_lottery_number[row].number[1]
				<< "," << m_vec_lottery_number[row].number[2]
				<< "," << m_vec_lottery_number[row].number[3]
				<< "," << m_vec_lottery_number[row].number[4]
				<< "," << m_vec_lottery_number[row].number[5]
				<< "," << m_vec_lottery_number[row].number[6]
				<< "," << m_vec_lottery_number[row].special_number;
			
			ln = m_vec_lottery_number[row];
			vector<double> vecFred;
			vector<int>	vecRegionStart;
			vector<int>	vecRegionEnd;
			ln = CalcCharacter(m_lottery_doc.m_lottery_info.regularnum, m_lottery_doc.m_lottery_info.totalnum,
				ln, vecRegionStart, vecRegionEnd,vecFred, false);

			ss << "," << ln.sum
				<< "," << ln.odd
				<< "," << ln.even
				<< ",\"" << ln.equal_tail << "\""
				<< ",\"" << consecutive_number_to_string(ln.Consecutive0) << "\""
				<< ",\"" << consecutive_number_to_string(ln.Consecutive1) << "\""
				<< ",\"" << consecutive_number_to_string(ln.Consecutive2) << "\""
				<< "," << Double2String(ln.var)
				<< "," << Double2String(ln.stdev)
				<< "," << Double2String(ln.devsq)
				<< "," << Double2String(ln.kurt)
				<< "," << Double2String(ln.skew)
				<< "," << ln.ac
				<< "," << ln.group_qty
				<< "," << ln.fringe_no_qty
				<< "," << Double2String(ln.fred)
				<< "," << ln.adjacent_interval[0]
				<< "," << ln.adjacent_interval[1]
				<< "," << ln.adjacent_interval[2]
				<< "," << ln.adjacent_interval[3]
				<< "," << ln.adjacent_interval[4]
				<< "," << ln.adjacent_interval[5];


			if (m_lottery_doc.m_lottery_info.specialnum)
			{
				ln = CalcCharacter(m_lottery_doc.m_lottery_info.regularnum, m_lottery_doc.m_lottery_info.totalnum, 
					ln, vecRegionStart, vecRegionEnd, vecFred, true);

				ss << "," << ln.sum
					<< "," << ln.odd
					<< "," << ln.even
					<< ",\"" << ln.equal_tail << "\""
					<< ",\"" << consecutive_number_to_string(ln.Consecutive0) << "\""
					<< ",\"" << consecutive_number_to_string(ln.Consecutive1) << "\""
					<< ",\"" << consecutive_number_to_string(ln.Consecutive2) << "\""
					<< "," << Double2String(ln.var)
					<< "," << Double2String(ln.stdev)
					<< "," << Double2String(ln.devsq)
					<< "," << Double2String(ln.kurt)
					<< "," << Double2String(ln.skew)
					<< "," << ln.ac
					<< "," << ln.group_qty
					<< "," << ln.fringe_no_qty
					<< "," << Double2String(ln.fred)
					<< "," << ln.adjacent_interval[0]
					<< "," << ln.adjacent_interval[1]
					<< "," << ln.adjacent_interval[2]
					<< "," << ln.adjacent_interval[3]
					<< "," << ln.adjacent_interval[4]
					<< "," << ln.adjacent_interval[5]
					<< "," << ln.adjacent_interval[6]
					<< "," << ln.special_first;
			}

			ss << endl;
			outfile << ss.str();
		}
		outfile.close();

		//	ͨ�� loaddata ���� mysql
		session sql(g_MysqlPool);
		sql << SqlScript();

		TCHAR path[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, path);
		sprintf_s(path, MAX_PATH, "%s\\%s", path, buffer);
		string strPath = ReplaceString(path, "\\", "/");

		ss.str("");
		ss << "load data infile "
			<< "\'" << strPath << "\'"
			<< " replace into table "
			<< " lottery_" << m_lottery_doc.m_lottery_info.code
			<< " character set gbk "
			<< " fields terminated by \',\' enclosed by \'\"\' ";
		string test = ss.str();
		sql << ss.str();

		//	ɾ����ʱ�ļ�
		DeleteFile(buffer);

		ss.str("");
		ss << m_lottery_doc.m_lottery_info.name;
		ss << "�����º��� " << ln.number[0];
		ss << "," << ln.number[1];
		ss << "," << ln.number[2];
		ss << "," << ln.number[3];
		ss << "," << ln.number[4];
		ss << ", �������� " << m_vec_lottery_number.size();
		ss << " OK, ���ݵ������. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		return;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		string test = ss.str();
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//	ɾ����ʱ�ļ�
		DeleteFile(buffer);
	}
}

bool CCalcLotteryNumberEnum::NeedGenerate(void)
{
	stringstream ss;
	long long c = 1;
	try {
		// ����� lottery Ӧ�þ��е������
		int n = m_lottery_doc.m_lottery_info.totalnum;
		for (int i = 0; i < m_lottery_doc.m_lottery_info.regularnum; i++)
		{
			c = c * n;
			n--;
		}
		n = 1;
		for (int i = 1; i <= m_lottery_doc.m_lottery_info.regularnum; i++)
		{
			n = n * i;
		}
		c = c / n;

		if (m_lottery_doc.m_lottery_info.specialnum)
		{
			c = c * (m_lottery_doc.m_lottery_info.totalnum - m_lottery_doc.m_lottery_info.regularnum);
		}

		//////////////////////////////////////////////////////////////////////////
		ss << "select count(*) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
		string test = ss.str();

		row r;
		session sql(g_MysqlPool);
		sql << SqlScript();
		sql << ss.str(), into(r);
		assert(r.size() == 1);
		long long existCnt = r.get<long long>("cnt");

		if (c == existCnt)
		{
			ss.str("");
			ss << "�����С����ݿ����Ѵ���������ϵ� " << c << "����¼\r\n";
			sendToOutput(ss.str().c_str(), NULL /*m_hWnd*/, m_nLogType);
			return false;
		}
		else if(existCnt > 0)
		{
			//	ȷ���ϴ�������ɵļ�¼��
			ss.str("");
			ss << "select max(number_1) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
			sql << ss.str(), into(r);
			m_max_1 = (int)r.get<int>("cnt", 0);

			ss.str("");
			ss << "select max(number_2) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
			ss << " where number_1 = " << m_max_1;
			sql << ss.str(), into(r);
			m_max_2 = (int)r.get<int>("cnt", 0);

			ss.str("");
			ss << "select max(number_3) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
			ss << " where number_1 = " << m_max_1;
			ss << " and number_2 = " << m_max_2;
			sql << ss.str(), into(r);
			m_max_3 = (int)r.get<int>("cnt", 0);

			ss.str("");
			ss << "select max(number_4) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
			ss << " where number_1 = " << m_max_1;
			ss << " and number_2 = " << m_max_2;
			ss << " and number_3 = " << m_max_3;
			sql << ss.str(), into(r);
			m_max_4 = (int)r.get<int>("cnt", 0);

			ss.str("");
			ss << "select max(number_5) as cnt from lottery_" << m_lottery_doc.m_lottery_info.code;
			ss << " where number_1 = " << m_max_1;
			ss << " and number_2 = " << m_max_2;
			ss << " and number_3 = " << m_max_3;
			ss << " and number_4 = " << m_max_4;
			sql << ss.str(), into(r);
			m_max_5 = (int)r.get<int>("cnt", 0);
		}

	}
	catch (std::exception const & e)
	{
		
	}

	ss.str("");
	ss << m_lottery_doc.m_lottery_info.name;
	if (m_max_1 > 0)
	{
		ss << "�ϴ����ɵ�������Ϊ ";
		ss << m_max_1 << "," << m_max_2 << "," << m_max_3 << "," << m_max_4 << "," << m_max_5;
	}
	ss << "����ҪԤ������ " << c << "����¼\r\n";
	sendToOutput(ss.str().c_str(), NULL /*m_hWnd*/, m_nLogType);

	return true;
}

void CCalcLotteryNumberEnum::Execute()
{
	/*������Ҫ���ز��񱨱�Ĺ�Ʊ*/
	stringstream ss;
	m_vec_lottery_number.clear();

	try{
		//////////////////////////////////////////////////////////////////////////
		//	�����������
		if (NeedGenerate())
		{
			for (int n1 = 1; n1 <= m_lottery_doc.m_lottery_info.totalnum; n1++)
			{
				for (int n2 = n1 + 1; n2 <= m_lottery_doc.m_lottery_info.totalnum; n2++)
				{
					for (int n3 = n2 + 1; n3 <= m_lottery_doc.m_lottery_info.totalnum; n3++)
					{
						for (int n4 = n3 + 1; n4 <= m_lottery_doc.m_lottery_info.totalnum; n4++)
						{
							for (int n5 = n4 + 1; n5 <= m_lottery_doc.m_lottery_info.totalnum; n5++)
							{
								if (m_lottery_doc.m_lottery_info.regularnum > 5)
								{
									for (int n6 = n5 + 1; n6 <= m_lottery_doc.m_lottery_info.totalnum; n6++)
									{
										if (m_lottery_doc.m_lottery_info.regularnum > 6)
										{
											for (int n7 = n6 + 1; n7 <= m_lottery_doc.m_lottery_info.totalnum; n7++)
											{
												LotteryNumber  lo;
												lo.number[0] = n1;
												lo.number[1] = n2;
												lo.number[2] = n3;
												lo.number[3] = n4;
												lo.number[4] = n5;
												lo.number[5] = n6;
												lo.number[6] = n7;
												EnumSpecialNumber(lo);
											}
										}
										else
										{
											LotteryNumber  lo;
											lo.number[0] = n1;
											lo.number[1] = n2;
											lo.number[2] = n3;
											lo.number[3] = n4;
											lo.number[4] = n5;
											lo.number[5] = n6;
											EnumSpecialNumber(lo);
										}
									}
								}
								else
								{
									LotteryNumber  lo;
									lo.number[0] = n1;
									lo.number[1] = n2;
									lo.number[2] = n3;
									lo.number[3] = n4;
									lo.number[4] = n5;
									EnumSpecialNumber(lo);
								}
							}
						}
					}
				}
			}

			ImportToDatabase();
		}
		
		//////////////////////////////////////////////////////////////////////////
		//	 �������õ����������� �����ݿ��й��� ��ѡ���� 

		bool bSpecial = false;
		if (m_lottery_doc.m_bContainSpecial && m_lottery_doc.m_lottery_info.specialnum > 0)
			bSpecial = true;

		// ��ȡ�����ѿ����ĺ���
		vector<LotteryNumber> vecln = m_lottery_doc.FetchAwardRecord();

		// ��ֵ����Ԥ����
		map<int, Assignment> mapPai = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_pai_start,m_lottery_doc.m_pai_end,m_lottery_doc.m_pai_analysis_periods);
		map<int, Assignment> mapLnPai = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_ln_pai_start, m_lottery_doc.m_ln_pai_end, m_lottery_doc.m_ln_pai_analysis_periods);
		map<int, Assignment> mapSwingPower = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_swing_start, m_lottery_doc.m_swing_end, m_lottery_doc.m_swing_analysis_periods);
		map<int, Assignment> mapLnSwing = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_ln_swing_start, m_lottery_doc.m_ln_swing_end, m_lottery_doc.m_ln_swing_analysis_periods);
		map<int, Assignment> mapBernoulli = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_bernoulli_start, m_lottery_doc.m_bernoulli_end, m_lottery_doc.m_bernoulli_analysis_periods);
		map<int, Assignment> mapPotential = m_lottery_doc.AssignmentFilterPre(vecln, m_lottery_doc.m_potential_start, m_lottery_doc.m_potential_end, m_lottery_doc.m_potential_analysis_periods);

		session sql(g_MysqlPool);
		string test;

		// ���������Դ�����ȵ�������Դ�����ݿ��е���ʱ�ļ���
		if (m_lottery_doc.m_strDataSource.IsEmpty() == false)
		{
			vector<string> arrayHeader;
			vector<vector<string>> arrayData;
			CCSVFile csvFile(m_lottery_doc.m_strDataSource.GetBuffer());
			csvFile.ReadAllData(arrayHeader, arrayData);
			csvFile.Close();

			int nExpected = m_lottery_doc.m_lottery_info.regularnum + (bSpecial? 1 : 0);
			if (arrayHeader.size() != nExpected)
			{
				ss.str("");
				ss << _T("�����ļ�������ƥ�䣡");
				ss << _T("��������Ϊ ") << nExpected;
				ss << _T("��������Ϊ ") << arrayHeader.size();
				ss << "\r\n";
				sendToOutput(ss.str().c_str(), NULL, m_nLogType);

				theApp.m_bRunning = FALSE;
				return;
			}

			string tableCode = m_lottery_doc.m_lottery_info.code;
			ss.str("");
			ss << "create temporary table if not exists lottery_tmp_" << tableCode
				<< "( number_t1 int, number_t2 int, number_t3 int, number_t4 int, number_t5 int ";
			if (m_lottery_doc.m_lottery_info.regularnum > 5)	ss << ", number_t6 int ";
			if (m_lottery_doc.m_lottery_info.regularnum > 6)	ss << ", number_t7 int";
			if (bSpecial)	ss << ", special_tnumber int ";
			ss << ", PRIMARY KEY ( number_t1, number_t2, number_t3, number_t4, number_t5 ";
			if (m_lottery_doc.m_lottery_info.regularnum > 5)	ss << ", number_t6 ";
			if (m_lottery_doc.m_lottery_info.regularnum > 6)	ss << ", number_t7 ";
			if (bSpecial)	ss << ", special_tnumber ";
			ss << " ))";
			
			test = ss.str();
			sql << ss.str();

			ss.str("");
			ss << "delete from lottery_tmp_" << tableCode;
			sql << ss.str();

			string strPath = m_lottery_doc.m_strDataSource.GetBuffer();
			strPath = ReplaceString(strPath, "\\", "/");
			ss.str("");
			ss << "load data infile "
				<< "\'" << strPath << "\'"
				<< " ignore into table "
				<< " lottery_tmp_" << tableCode
				<< " character set gbk "
				<< " fields terminated by \',\' enclosed by \'\"\' "
				<< " lines terminated by '\n' ";
			ss << "( number_t1 , number_t2 , number_t3 , number_t4 , number_t5  ";
			if (m_lottery_doc.m_lottery_info.regularnum > 5)	ss << ", number_t6  ";
			if (m_lottery_doc.m_lottery_info.regularnum > 6)	ss << ", number_t7 ";
			if (bSpecial)	ss << ", special_tnumber ";
			ss << " ) ";
			test = ss.str();
			sql << ss.str();

			row r;
			ss.str("");
			ss << "delete from lottery_tmp_" << tableCode;
			ss << " where number_t1=0";
			sql << ss.str();

			ss.str("");
			ss << "select count(*) as cnt from lottery_tmp_" << tableCode;
			sql << ss.str(), into(r);
			int nImported = (int)r.get<long long>("cnt", 0);

			ss.str("");
			ss << "��������Դ " << m_lottery_doc.m_strDataSource;
			if (nImported > 0)
				ss << _T(", �ɹ����� ") << nImported << "��";
			else
				ss << _T(", ��ʽ���ԣ���˶��Ƿ�ƥ���ر�ŵ�����");
			ss << "\r\n";
			sendToOutput(ss.str().c_str(), NULL, m_nLogType);
			
			ss.str("");
			ss << " lottery_tmp_" << tableCode << " where 1 = 1 "
				<< " and lottery_" << tableCode << ".number_1 = " << " lottery_tmp_" << tableCode << ".number_t1 "
				<< " and lottery_" << tableCode << ".number_2 = " << " lottery_tmp_" << tableCode << ".number_t2 "
				<< " and lottery_" << tableCode << ".number_3 = " << " lottery_tmp_" << tableCode << ".number_t3 "
				<< " and lottery_" << tableCode << ".number_4 = " << " lottery_tmp_" << tableCode << ".number_t4 "
				<< " and lottery_" << tableCode << ".number_5 = " << " lottery_tmp_" << tableCode << ".number_t5 ";
			if (m_lottery_doc.m_lottery_info.regularnum > 5)
				ss << " and lottery_" << tableCode << ".number_6 = " << " lottery_tmp_" << tableCode << ".number_t6 ";
			if (m_lottery_doc.m_lottery_info.regularnum > 6)	
				ss << " and lottery_" << tableCode << ".number_7 = " << " lottery_tmp_" << tableCode << ".number_t7 ";
			if (bSpecial)
				ss << " and lottery_" << tableCode << ".special_number = " << " lottery_tmp_" << tableCode << ".special_tnumber ";
			else if (m_lottery_doc.m_lottery_info.specialnum > 0)
				ss << " and lottery_" << tableCode << ".special_first = 1";
			
			test = m_lottery_doc.SelectClause(ss.str());
		}
		else
			test = m_lottery_doc.SelectClause();

		test += m_lottery_sql;
		//test = Gbk2Utf8(test);
		long cnt = 0;
		int nPage = 0;
		int nRecord = 0;
		ofstream outfile(m_file_path.c_str(), ofstream::out);

		while (true)
		{
			bool isEnd = true;

			stringstream ss;
			ss << test << " limit " << Int2String(nPage * 500000) << ", 500000";
			string test1 = ss.str();

			row r;
			statement st = (sql.prepare << test1, into(r));
			st.execute();

			ss.str("");
			ss << "�����С���" << (nPage + 1) << "�ֿ�ʼ\r\n";
			sendToOutput(ss.str().c_str(), NULL, m_nLogType);
			nRecord = 0;

			while (st.fetch())
			{
				nRecord++;
				isEnd = false;
				
				LotteryNumber ln;
				ln.name = r.get<string>("name", "");
				ln.number[0] = r.get<int>("number_1", 0);
				ln.number[1] = r.get<int>("number_2", 0);
				ln.number[2] = r.get<int>("number_3", 0);
				ln.number[3] = r.get<int>("number_4", 0);
				ln.number[4] = r.get<int>("number_5", 0);
				ln.number[5] = r.get<int>("number_6", 0);
				ln.number[6] = r.get<int>("number_7", 0);
				if (bSpecial)
					ln.special_number = r.get<int>("special_number", 0);
				else
					ln.special_number = 0;

				int nRet = 0;
				// ���Ź���
				nRet = m_lottery_doc.ConsecutiveFilter(r.get<string>("consecutive0", ""),
					r.get<string>("consecutive1", ""), r.get<string>("consecutive2", ""));
				m_lottery_doc.FilterStatistic(_T("01. ���Ź���"), nRet);
				if (nRet < 0)
					continue;

				//	��ͬβ������
				nRet = m_lottery_doc.TailFilter(r.get<string>("equal_tail", ""));
				m_lottery_doc.FilterStatistic(_T("02. ��ͬβ������"), nRet);
				if (nRet < 0)
					continue;

				//  fred ����
				nRet = m_lottery_doc.FredFilter(r.get<int>("sum_number", 0),
					r.get<int>("ac", 0.0), r.get<int>("fringe_no_qty", 0), r.get<int>("group_qty", 0));
				m_lottery_doc.FilterStatistic(_T("03. fred ����"), nRet);
				if (nRet < 0)
					continue;

				//  �ѿ������� ��ͬ���� ����
				nRet = m_lottery_doc.EqualNumberFilter(vecln, ln.number);
				m_lottery_doc.FilterStatistic(_T("04. �ѿ���������ͬ��������"), nRet);
				if (nRet < 0)
					continue;

				//	�и�ֵ
				nRet = m_lottery_doc.PaiFilter(mapPai, ln);
				m_lottery_doc.FilterStatistic(_T("05. �и�ֵ"), nRet);
				if (nRet < 0)
					continue;

				//	ln�и�ֵ
				nRet = m_lottery_doc.LnPaiFilter(mapLnPai, ln);
				m_lottery_doc.FilterStatistic(_T("06. ln�и�ֵ"), nRet);
				if (nRet < 0)
					continue;

				//	�ǵ�������ֵ
				nRet = m_lottery_doc.SwingPowerFilter(mapSwingPower, ln);
				m_lottery_doc.FilterStatistic(_T("07. �ǵ�������ֵ"), nRet);
				if (nRet < 0)
					continue;

				//	ln �ǵ�������ֵ
				nRet = m_lottery_doc.LnSwingPowerFilter(mapLnSwing, ln);
				m_lottery_doc.FilterStatistic(_T("08. ln�ǵ�������ֵ"), nRet);
				if (nRet < 0)
					continue;

				//	bernoulli ��ֵ
				nRet = m_lottery_doc.BernoulliFilter(mapBernoulli, ln);
				m_lottery_doc.FilterStatistic(_T("09. bernoulli ��ֵ"), nRet);
				if (nRet < 0)
					continue;

				//	potential ���� ��ֵ
				nRet = m_lottery_doc.PotentialFilter(mapPotential, ln);
				m_lottery_doc.FilterStatistic(_T("10. potential ����"), nRet);
				if (nRet < 0)
					continue;

				// 
				nRet = m_lottery_doc.RegularExpressFilter(ln);
				m_lottery_doc.FilterStatistic(_T("11. �ļ�����(����)"), nRet);
				if (nRet < 0)
					continue;

				//  �ѿ������� ������������
				nRet = m_lottery_doc.ArithmeticCorrectFilter(vecln, ln.number);
				m_lottery_doc.FilterStatistic(_T("12. �ѿ�������������������"), nRet);
				if (nRet < 0)
					continue;
				//////////////////////////////////////////////////////////////////////////////////////////
				// ����������ļ�
				
				if (cnt >= 20 * 10000)
				{
					isEnd = true;
					ss.str("");
					ss << "���ɺ��볬�� 20 ��������ֹ�����С�\r\n";
					sendToOutput(ss.str().c_str(), NULL /*m_hWnd*/, m_nLogType);
					break;
				}
				if (cnt % 10000 == 0 && cnt > 0)
				{
					ss.str("");
					ss << "�����С��Ѿ����ɺ��� " << cnt / 10000 << "����\r\n";
					sendToOutput(ss.str().c_str(), NULL /*m_hWnd*/, m_nLogType);
				}

				ss.str("");
				ss << Int2String(ln.number[0], "%02d")
					<< "," << Int2String(ln.number[1], "%02d")
					<< "," << Int2String(ln.number[2], "%02d")
					<< "," << Int2String(ln.number[3], "%02d")
					<< "," << Int2String(ln.number[4], "%02d");
				if (m_lottery_doc.m_lottery_info.regularnum >= 6)	ss << "," << Int2String(ln.number[5], "%02d");
				if (m_lottery_doc.m_lottery_info.regularnum >= 7)	ss << "," << Int2String(ln.number[6], "%02d");
				if (bSpecial)	ss << "," << Int2String(ln.special_number, "%02d");

				ss << endl;
				outfile << ss.str();
				cnt++;
			}

			ss.str("");
			ss << "�����С���" << (nPage + 1) << "�ֽ����������� " << nRecord <<" ����¼ \r\n";
			sendToOutput(ss.str().c_str(), NULL, m_nLogType);

			if (isEnd)
				break;
			nPage++;
		}
		
		outfile.close();
		if (cnt == 0)
		{
			DeleteFile(m_file_path.c_str());
		}
		else
		{
			// ����Դ�������е�������ѡ���ļ�
			CString strParam;
			strParam.Format(" /select, %s", m_file_path.c_str());
			SHELLEXECUTEINFO shex = { 0 };
			shex.cbSize = sizeof(SHELLEXECUTEINFO);
			shex.lpFile = _T("explorer");
			shex.lpParameters = strParam.GetBuffer();
			shex.lpVerb = NULL;  // _T("open");	
			shex.nShow = SW_SHOWDEFAULT;
			shex.lpDirectory = NULL;
			ShellExecuteEx(&shex);
		}

		ss.str("");
		ss << "�����С���Ʊ���������ɣ� ����" << cnt << "����¼\r\n";
		sendToOutput(ss.str().c_str(), NULL /*m_hWnd*/, m_nLogType);

		m_lottery_doc.FilterStatisticPrint();
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}

	theApp.m_bRunning = FALSE;
}
