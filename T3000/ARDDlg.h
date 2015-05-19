#pragma once
#include "MainFrm.h"
#include "afxcmn.h"
#include "afxwin.h"

// CARDDlg dialog

class CARDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CARDDlg)

public:
	CARDDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CARDDlg();
	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_REMOTE_CONNECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_ipaddress;
	CEdit m_porteditor;
	vector<CString> m_szComm;
	CComboBox m_add_device_com_port;
	CComboBox m_add_device_baudrate;
	CEdit m_add_device_modbus_id;
	void Enable_Net_UI(bool enable_net);
	afx_msg void OnBnClickedRadioNetDevice();
	afx_msg void OnBnClickedRadio2();
	bool m_is_net_device;
	afx_msg void OnBnClickedButtonLocalMstpDevice();

// 	_ConnectionPtr				m_pCon;//for ado connection
// 	_RecordsetPtr				m_pRs;//for ado 
};