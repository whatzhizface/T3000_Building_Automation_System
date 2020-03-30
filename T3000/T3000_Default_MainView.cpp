// T3000_Default_MainView.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "T3000_Default_MainView.h"
#include "MainFrm.h"
 #include "../SQLiteDriver/CppSQLite3.h"

// T3000_Default_MainView
extern tree_product selected_product_Node; // 选中的设备信息;
IMPLEMENT_DYNCREATE(T3000_Default_MainView, CFormView)

T3000_Default_MainView::T3000_Default_MainView()
	: CFormView(T3000_Default_MainView::IDD)
{
	m_checkpassword = true;
}

T3000_Default_MainView::~T3000_Default_MainView()
{
}

void T3000_Default_MainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPMODEL_COMBO, m_ip_model);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Control(pDX, IDC_IPADDRESS2, m_Subnet_Mask);
	DDX_Control(pDX, IDC_IPADDRESS3, m_GatewayAddress);
	DDX_Control(pDX, IDC_MAC_ADDRESS, m_Edit_MacAddress);
	DDX_Control(pDX, IDC_EDIT_LISTENPORT, m_ListenPort);
	DDX_Control(pDX, IDC_BAUDRATECOMBO, m_brandrate_combox);
	DDX_Control(pDX, IDC_EDIT_MSTP_MAC, m_Editor_macmstp);
	DDX_Control(pDX, IDC_COMBO_MSTP_MODBUS, m_mstpmodbus_combox);
	DDX_Control(pDX, IDC_EDIT_BIPPORT, m_BipPort_Edit);
	DDX_Control(pDX, IDC_EDIT_AES_ENCRYPT, m_Edit_AESPassword);
	DDX_Control(pDX, IDC_COMBO_MRD, m_combox_mrd);
	DDX_Control(pDX, IDC_EDIT_NETWORKID, m_Edit_Network);
	DDX_Control(pDX, IDC_EDIT_NODEID, m_Edit_NodeID);
	DDX_Control(pDX, IDC_EDIT_FREID, m_Edit_FrequenceID);
}

BEGIN_MESSAGE_MAP(T3000_Default_MainView, CFormView)
	ON_BN_CLICKED(IDC_EDIT_ID, &T3000_Default_MainView::OnBnClickedEditId)
  
    ON_BN_CLICKED(IDC_APPLYBUTTON, &T3000_Default_MainView::OnBnClickedApplybutton)
    ON_CBN_SELCHANGE(IDC_IPMODEL_COMBO, &T3000_Default_MainView::OnCbnSelchangeIpmodelCombo)
	ON_EN_KILLFOCUS(IDC_EDIT_BIPPORT, &T3000_Default_MainView::OnEnKillfocusEditBipport)
	ON_CBN_SELCHANGE(IDC_COMBO_MSTP_MODBUS, &T3000_Default_MainView::OnCbnSelchangeComboMstpModbus)
	ON_EN_KILLFOCUS(IDC_EDIT_MSTP_MAC, &T3000_Default_MainView::OnEnKillfocusEditMstpMac)
	ON_CBN_KILLFOCUS(IDC_BAUDRATECOMBO, &T3000_Default_MainView::OnCbnKillfocusBaudratecombo)
	ON_BN_CLICKED(IDC_BUTTON_WIFI_CONFIG, &T3000_Default_MainView::OnBnClickedButtonWifiConfig)
	ON_BN_CLICKED(IDC_CHECK_PASSWORD, &T3000_Default_MainView::OnBnClickedCheckPassword)
	ON_CBN_SELCHANGE(IDC_COMBO_MRD, &T3000_Default_MainView::OnCbnSelchangeComboMrd)
	ON_EN_KILLFOCUS(IDC_EDIT_AES_ENCRYPT, &T3000_Default_MainView::OnEnKillfocusEditAesEncrypt)
	ON_EN_KILLFOCUS(IDC_EDIT_NETWORKID, &T3000_Default_MainView::OnEnKillfocusEditNetworkid)
	ON_EN_KILLFOCUS(IDC_EDIT_NODEID, &T3000_Default_MainView::OnEnKillfocusEditNodeid)
	ON_EN_KILLFOCUS(IDC_EDIT_FREID, &T3000_Default_MainView::OnEnKillfocusEditFreid)
    ON_EN_CHANGE(IDC_EDIT_AES_ENCRYPT, &T3000_Default_MainView::OnEnChangeEditAesEncrypt)
    ON_EN_KILLFOCUS(IDC_EDIT_BACNET_DEVICE_ID, &T3000_Default_MainView::OnEnKillfocusEditBacnetDeviceId)
    ON_CBN_SELCHANGE(IDC_BAUDRATECOMBO, &T3000_Default_MainView::OnCbnSelchangeBaudratecombo)
END_MESSAGE_MAP()


// T3000_Default_MainView diagnostics

#ifdef _DEBUG
void T3000_Default_MainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void T3000_Default_MainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// T3000_Default_MainView message handlers


void T3000_Default_MainView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	 
}

void T3000_Default_MainView::Fresh(){
    CString strTemp;
	strTemp.Format(_T("%d"),g_tstat_id);
	GetDlgItem(IDC_ID_EDIT)->SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),get_serialnumber());
	GetDlgItem(IDC_SERIALNUM_EDIT)->SetWindowTextW(strTemp);

	m_brandrate_combox.ResetContent();
    if ((product_register_value[7] == PM_CS_SM_DC) ||
        (product_register_value[7] == PM_CS_SM_AC))
    {
        m_brandrate_combox.AddString(L"9600");
        m_brandrate_combox.AddString(L"19200");
        if (product_register_value[141] == 0)
        {
            m_brandrate_combox.SetWindowTextW(_T("19200"));
        }
        else
        {
            m_brandrate_combox.SetWindowTextW(_T("9600"));
        }
    }
    else
    {
        m_brandrate_combox.AddString(L"9600");
        m_brandrate_combox.AddString(L"19200");
        m_brandrate_combox.AddString(L"38400");
        m_brandrate_combox.AddString(L"57600");
        m_brandrate_combox.AddString(L"115200");
        m_brandrate_combox.AddString(L"76800");

        if ((product_register_value[15] >= 0) && (product_register_value[15] <= 5))
            m_brandrate_combox.SetCurSel(product_register_value[15]);
    }


	m_mstpmodbus_combox.ResetContent();
	m_mstpmodbus_combox.AddString(L"BACnet MSTP");
 
	m_mstpmodbus_combox.AddString(L"Modbus");
	 
    unsigned short temp_high;
    unsigned short temp_low;
    Get_Instance_Reg_Map(product_register_value[7], temp_high, temp_low);

    unsigned int temp_device_id;
    temp_device_id = product_register_value[temp_high] * 65536 + product_register_value[temp_low];
    CString cs_deviceid;
    cs_deviceid.Format(_T("%u"), temp_device_id);

    GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->SetWindowTextW(cs_deviceid);

	if (product_register_value[7] == PM_TSTAT8|| 
        product_register_value[7] == PM_TSTAT9 ||
        product_register_value[7] == PM_TSTAT_AQ ||
        product_register_value[7] == PM_MULTI_SENSOR ||
        (product_register_value[7] == PM_TSTAT8_WIFI) || 
        (product_register_value[7] == PM_TSTAT8_OCC) || 
        (product_register_value[7] == PM_TSTAT7_ARM) || 
        (product_register_value[7] == PM_TSTAT8_220V))
	{
		if (product_register_value[21] == 0)
		{
			m_mstpmodbus_combox.SetCurSel(1);
		}

		else
		{
			m_mstpmodbus_combox.SetCurSel(0);
		}

        if (product_register_value[4] >= 86)
        {
            GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->EnableWindow(true);
        }
        else
        {
            GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->EnableWindow(false);
        }
	}
    else if ((product_register_value[7] == PM_CS_SM_AC) ||
        (product_register_value[7] == PM_CS_SM_DC) ||
        (product_register_value[7] == PM_CS_RSM_AC) ||
        (product_register_value[7] == PM_CS_RSM_DC))
    {
        m_mstpmodbus_combox.SetWindowTextW(_T("Modbus"));
        m_mstpmodbus_combox.EnableWindow(0);
        GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->EnableWindow(0);
    }
	else
	{
        if (product_register_value[4] >= 36)
            GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->EnableWindow(true);
        else
            GetDlgItem(IDC_EDIT_BACNET_DEVICE_ID)->EnableWindow(false);
		if (product_register_value[21] == 0)
		{
			m_mstpmodbus_combox.SetCurSel(0);
		}

		else
		{
			m_mstpmodbus_combox.SetCurSel(1);
		}
	}


	strTemp.Format(_T("%d"), product_register_value[39]);
	m_Editor_macmstp.SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"), product_register_value[38]);
	m_BipPort_Edit.SetWindowTextW(strTemp);

	strTemp.Format(_T("%0.1f"),get_curtstat_version());
	GetDlgItem(IDC_FIRMWARV_EDIT)->SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),product_register_value[8]);//8
	GetDlgItem(IDC_HARDWAREV_EDIT)->SetWindowTextW(strTemp);
	int nModel=product_register_value[7];
	CString ProductName = GetProductName(nModel);
	if (nModel == PM_CS_RSM_AC||nModel == PM_CS_SM_AC)
	{
		if (product_register_value[11] == 0)
		{
			ProductName+=_T("-100A");
		}
		else if (product_register_value[11]==1)
		{
			ProductName+=_T("-200A");
		}
		else if (product_register_value[11]==2)
		{
			ProductName+=_T("-300A");
		}

	}
	
	GetDlgItem(IDC_MODEL_EDIT)->SetWindowTextW(ProductName);
	strTemp.Format(_T("%d"),product_register_value[9]);
	GetDlgItem(IDC_PIC_EDIT)->SetWindowText(strTemp);



	GetDlgItem(IDC_BUTTON_WIFI_CONFIG)->ShowWindow(TRUE);
	MODBUS_BAUDRATE = 15;
    if (             product_register_value[7] == PM_T322AI 
	              || product_register_value[7] == PM_T38AI8AO6DO 
	              || product_register_value[7] == PM_T3PT12
				  || product_register_value[7] == PM_T36CTA
                  || product_register_value[7] == PM_PWMETER
	              ||product_register_value[7]==STM32_HUM_NET 
		)
    {
        GetDlgItem (IDC_STATIC_IPTIPS)->ShowWindow (TRUE);
        GetDlgItem (IDC_APPLYBUTTON)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_IPMODEL)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_IPADDRESS)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICSUBNETMASK)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICGATEWAYADDRESS)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_LISTENNINGPORT)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICMACADDRESS)->ShowWindow (TRUE);
		
        CString strtemp;
        int CO2_NET_MODBUS_MAC_ADDRESS_START = 40;
        strtemp.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+1],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+2],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+3],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+4],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+5]);
        m_Edit_MacAddress.SetWindowText(strtemp);
        m_Edit_MacAddress.ShowWindow (TRUE);
        int CO2_NET_MODBUS_IP_MODE = 46;
        m_ip_model.SetCurSel(product_register_value[CO2_NET_MODBUS_IP_MODE]);
        m_ip_model.ShowWindow (TRUE);
        int   CO2_NET_MODBUS_IP_ADDRESS_START = 47;
        m_ipaddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+3]);
         int   CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START  =     51;
          m_ipaddress.ShowWindow (TRUE);
        m_Subnet_Mask.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+3]);
             int   CO2_NET_MODBUS_GATEWAY_ADDRESS_START  =     55;
             m_Subnet_Mask.ShowWindow (TRUE);

        m_GatewayAddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+3]);
          int CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START =  60;
          m_GatewayAddress.ShowWindow (TRUE);
        strtemp.Format(_T("%d"),product_register_value[CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START]);
        m_ListenPort.SetWindowText(strtemp);
        m_ListenPort.ShowWindow (TRUE);


    }
	
	else if ( product_register_value[7] == PM_TSTAT8_WIFI)
	{
		 
			GetDlgItem(IDC_STATIC_IPTIPS)->ShowWindow(TRUE);
			GetDlgItem(IDC_APPLYBUTTON)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_IPMODEL)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_IPADDRESS)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATICSUBNETMASK)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATICGATEWAYADDRESS)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_LISTENNINGPORT)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATICMACADDRESS)->ShowWindow(TRUE);
			GetDlgItem(IDC_BUTTON_WIFI_CONFIG)->ShowWindow(TRUE);
	 
		   
		

		GetDlgItem(IDC_STATIC_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_MSTP)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_MSTP_MAC)->ShowWindow(FALSE);


		CString strtemp;
		int CO2_NET_MODBUS_MAC_ADDRESS_START = 40;
		strtemp.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"), product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START], product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START + 1], product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START + 2], product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START + 3], product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START + 4], product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START + 5]);
		m_Edit_MacAddress.SetWindowText(strtemp);
		m_Edit_MacAddress.ShowWindow(TRUE);
		int CO2_NET_MODBUS_IP_MODE = 46;
		m_ip_model.SetCurSel(product_register_value[CO2_NET_MODBUS_IP_MODE]);
		m_ip_model.ShowWindow(TRUE);
		 
		int   CO2_NET_MODBUS_IP_ADDRESS_START = 47;
		m_ipaddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START],
			(BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START + 1],
			(BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START + 2],
			(BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START + 3]);
		int   CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START = 51;
		m_ipaddress.ShowWindow(TRUE);
		m_Subnet_Mask.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START],
			(BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START + 1],
			(BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START + 2],
			(BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START + 3]);
		int   CO2_NET_MODBUS_GATEWAY_ADDRESS_START = 55;
		m_Subnet_Mask.ShowWindow(TRUE);

		m_GatewayAddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START],
			(BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START + 1],
			(BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START + 2],
			(BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START + 3]);
		int CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START = 60;
		m_GatewayAddress.ShowWindow(TRUE);
		strtemp.Format(_T("%d"), product_register_value[CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START]);
		m_ListenPort.SetWindowText(strtemp);
		m_ListenPort.ShowWindow(TRUE);
	}
	else if(product_register_value[7] == PWM_TRANSDUCER)
	{
		GetDlgItem(IDC_STATIC_IPTIPS)->ShowWindow(FALSE);
		GetDlgItem(IDC_APPLYBUTTON)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IPMODEL)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IPADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICSUBNETMASK)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICGATEWAYADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_LISTENNINGPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICMACADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_MSTP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MSTP_MODBUS)->ShowWindow(FALSE);

		m_Edit_MacAddress.ShowWindow(FALSE);
		m_ip_model.ShowWindow(FALSE);
		m_ipaddress.ShowWindow(FALSE);
		m_Subnet_Mask.ShowWindow(FALSE);
		m_GatewayAddress.ShowWindow(FALSE);
		m_ListenPort.ShowWindow(FALSE);
		m_Editor_macmstp.ShowWindow(FALSE);
		m_mstpmodbus_combox.ShowWindow(FALSE);
		m_BipPort_Edit.ShowWindow(FALSE);


	}
    else if ((product_register_value[7] == PM_TSTAT_AQ) ||
             (product_register_value[7] == PM_TSTAT9) ||
             (product_register_value[7] == PM_TSTAT8) ||
             (product_register_value[7] == PM_TSTAT10) ||
             (product_register_value[7] == PM_MULTI_SENSOR))
    {
        GetDlgItem(IDC_STATIC_IPTIPS)->ShowWindow(FALSE);
        GetDlgItem(IDC_APPLYBUTTON)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_IPMODEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_IPADDRESS)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATICSUBNETMASK)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATICGATEWAYADDRESS)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_LISTENNINGPORT)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATICMACADDRESS)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_AEC_ENCRYPT)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_AES_ENCRYPT)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_PASSWORD)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_ACE)->ShowWindow(FALSE);
        
        GetDlgItem(IDC_STATIC_BIPPORT)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_BIPPORT)->ShowWindow(FALSE);
        m_Edit_MacAddress.ShowWindow(FALSE);
        m_ip_model.ShowWindow(FALSE);
        m_ipaddress.ShowWindow(FALSE);
        m_Subnet_Mask.ShowWindow(FALSE);
        m_GatewayAddress.ShowWindow(FALSE);
        m_ListenPort.ShowWindow(FALSE);
        GetDlgItem(IDC_BUTTON_WIFI_CONFIG)->ShowWindow(TRUE);
    }
	else
    {
        GetDlgItem (IDC_STATIC_IPTIPS)->ShowWindow (FALSE);
        GetDlgItem (IDC_APPLYBUTTON)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_IPMODEL)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_IPADDRESS)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICSUBNETMASK)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICGATEWAYADDRESS)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_LISTENNINGPORT)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICMACADDRESS)->ShowWindow (FALSE);
		GetDlgItem (IDC_STATIC_AEC_ENCRYPT)->ShowWindow(FALSE);
		GetDlgItem (IDC_EDIT_AES_ENCRYPT)->ShowWindow(FALSE);
		GetDlgItem (IDC_CHECK_PASSWORD)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_ACE)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_MSTP)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_MSTP_MAC)->ShowWindow(FALSE);


        m_Edit_MacAddress.ShowWindow (FALSE);
        m_ip_model.ShowWindow (FALSE);
        m_ipaddress.ShowWindow (FALSE);
        m_Subnet_Mask.ShowWindow (FALSE);
        m_GatewayAddress.ShowWindow (FALSE);
        m_ListenPort.ShowWindow (FALSE);
		GetDlgItem(IDC_STATIC_NETWORKID)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_NETWORKID2)->ShowWindow(FALSE);
				GetDlgItem(IDC_STATIC_NETWORKID3)->ShowWindow(FALSE);
					GetDlgItem(IDC_EDIT_NETWORKID)->ShowWindow(FALSE);
						GetDlgItem(IDC_EDIT_NODEID)->ShowWindow(FALSE);
							GetDlgItem(IDC_EDIT_FREID)->ShowWindow(FALSE);
    }

	if (product_register_value[7] == PM_TSTAT5i
		|| product_register_value[7] == PM_TSTAT6
		|| product_register_value[7] == PM_TSTAT7
		|| product_register_value[7] == PM_TSTAT8
        || product_register_value[7] == PM_TSTAT9
		|| (product_register_value[7] == PM_TSTAT8_WIFI) || (product_register_value[7] == PM_TSTAT8_OCC) || (product_register_value[7] == PM_TSTAT7_ARM) || (product_register_value[7] == PM_TSTAT8_220V)
		)
	{
		bitset<16>  value109(product_register_value[109]);
		int sel = value109[4];//第五位
		m_combox_mrd.SetCurSel(sel);
	}
	else
	{
		bitset<16>  value184(product_register_value[184]);
		int sel = value184[4];//第五位
		m_combox_mrd.SetCurSel(sel);
	}
	Read_Multi(g_tstat_id, &product_register_value[599], 599, 100);
	if (product_register_value[599] == 0)
	{
		m_Edit_AESPassword.EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PASSWORD)->EnableWindow(FALSE);
	} 
	else
	{
		m_Edit_AESPassword.EnableWindow(TRUE);
		m_Edit_AESPassword.SetWindowTextW(GetTextFromReg(600)+ GetTextFromReg(604));
		//m_Edit_AESPassword.SetPasswordChar('*');
		((CButton *)GetDlgItem(IDC_CHECK_PASSWORD))->SetCheck(1);
	}
	  strTemp.Format(_T("%d"), (int)product_register_value[608]);
	  m_Edit_Network.SetWindowTextW(strTemp);
	  strTemp.Format(_T("%d"), (int)product_register_value[609]);
	  m_Edit_NodeID.SetWindowTextW(strTemp);

	  long long Freq = ((long long)product_register_value[610]) * 65536 + ((long long)product_register_value[611]);
	  strTemp.Format(_T("%ld HZ"), Freq);
	  m_Edit_FrequenceID.SetWindowTextW(strTemp);

      if (PM_T36CTA == product_register_value[7])
      {
          m_Edit_FrequenceID.ShowWindow(SW_SHOW);
          GetDlgItem(IDC_STATIC_AEC_ENCRYPT)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_EDIT_AES_ENCRYPT)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_STATIC_NETWORKID)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_STATIC_NETWORKID2)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_STATIC_NETWORKID3)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_EDIT_NETWORKID)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_EDIT_NODEID)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_EDIT_FREID)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_STATIC_ACE)->ShowWindow(SW_SHOW);
          
      }
      else
      {
          m_Edit_FrequenceID.ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STATIC_AEC_ENCRYPT)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_EDIT_AES_ENCRYPT)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STATIC_NETWORKID)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STATIC_NETWORKID2)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STATIC_NETWORKID3)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_EDIT_NETWORKID)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_EDIT_NODEID)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_EDIT_FREID)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STATIC_ACE)->ShowWindow(SW_HIDE);
      }
      switch_product_last_view();
}
#include "EreaseDlg.h"

void T3000_Default_MainView::OnBnClickedEditId()
{
	 CEreaseDlg dlg;
	 dlg.DoModal();

     CString str;
     str.Format (_T("%d"),g_tstat_id);

     GetDlgItem (IDC_ID_EDIT)->SetWindowTextW(str);
}


//void T3000_Default_MainView::OnBnClickedButtonGoToInput()
//{
//     /* if (product_type == T3000_T3_MODULES )
//     {
//         SwitchToPruductType(DLG_DIALOG_T3_INPUTS_VIEW);
//    }*/
//    CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
//    pFrame->OnControlInputs ();
//}


void T3000_Default_MainView::OnBnClickedApplybutton()
{
    int m_nListenPort=0;
    BeginWaitCursor();
    //m_nListenPort	
    CString strText;
    m_ListenPort.GetWindowText(strText);
    if(!strText.IsEmpty())
        m_nListenPort=_wtoi(strText);
    if(m_nListenPort>=12767)
    {
        AfxMessageBox(_T("The listen port number is too big, please change it."));
        return;
    }
    if(m_nListenPort<=0)
    {
        AfxMessageBox(_T("The listen port number must be greater than 0!"));
        return;
    }
    write_one(g_tstat_id,75,m_nListenPort);
    product_register_value[75]=m_nListenPort;
    BYTE address1,address2,address3,address4;
    m_ipaddress.GetAddress(address1,address2,address3,address4);

    int sel = m_ip_model.GetCurSel ();
     write_one(g_tstat_id,61,sel);

    int CO2_NET_MODBUS_IP_ADDRESS_GHOST_START = 62 ;
    int n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+3,address4);
    int CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START = 66;
    m_Subnet_Mask.GetAddress(address1,address2,address3,address4);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+0,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+3,address4);
    m_GatewayAddress.GetAddress(address1,address2,address3,address4);
    int CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START =   70;
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+3,address4);
    int CO2_NET_MODBUS_ENABLE_GHOST = 76;
    n=write_one(g_tstat_id,CO2_NET_MODBUS_ENABLE_GHOST,1);

    Sleep(5*1000);



    CMainFrame* pPraent=(CMainFrame*)GetParent();

    CString strBuilding,strSubBuilding;
    strBuilding=pPraent->m_strCurMainBuildingName;
    strSubBuilding=pPraent->m_strCurSubBuldingName;
    CString strIP,strPort;
    strPort.Format(_T("%d"),product_register_value[75]);
    // BYTE address1,address2,address3,address4;
    m_ipaddress.GetAddress(address1,address2,address3,address4);
    strIP.Format(_T("%d.%d.%d.%d"),address1,address2,address3,address4);
    if(g_CommunicationType==1)//TCP
    {
       /* int nPort;
        nPort=_wtoi(strPort);*/
        //m_strIP=build_info.strIp; 
        g_CommunicationType=1;
        SetCommunicationType(g_CommunicationType);
        BOOL bOk=FALSE;
        bOk=Open_Socket2(strIP,m_nListenPort);
        CString strInfo;

        strInfo.Format((_T("Open IP:%s successful")),strIP);//prompt info;
        SetPaneString(1,strInfo);
        if(bOk)
        {
            try
			{
			CppSQLite3DB SqliteDBBuilding;
			CppSQLite3Table table;
			CppSQLite3Query q;
			SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);


                CString strSql;
                //strSql.Format(_T("update Building set Ip_Address='%s' where Ip_Address='%s'"),strIP,pPraent->m_strIP);
                //t_pCon->Execute(strSql.GetString(),NULL,adCmdText);

                // ¸Änode
                CString strSID;

                strSID.Format(_T("%d"), get_serialnumber());
                strSql.Format(_T("update ALL_NODE set Bautrate='%s',Com_Port='%s' where Serial_ID='%s'"),strIP,strPort,strSID); //bautrate ·ÅIP
                SqliteDBBuilding.execDML((UTF8MBSTR)strSql);

                SqliteDBBuilding.closedb();

            }
            catch(_com_error *e)
            {
                AfxMessageBox(e->ErrorMessage());
            }

            pPraent->m_strIP=strIP;
            pPraent->ScanTstatInDB();

        }
        else
        {

        }



    }
    EndWaitCursor();
}


void T3000_Default_MainView::OnCbnSelchangeIpmodelCombo()
{ 

}


void T3000_Default_MainView::OnEnKillfocusEditBipport()
{
	CString strTemp;
	m_BipPort_Edit.GetWindowTextW(strTemp);
	int ret = write_one(g_tstat_id, 38, _wtoi(strTemp));
	if (ret>0)
	{
		product_register_value[38] = _wtoi(strTemp);
	}
 
	
}


void T3000_Default_MainView::OnCbnSelchangeComboMstpModbus()
{
	int sel = m_mstpmodbus_combox.GetCurSel();
	int protocol = 0;
    bool  modbus_0_bacnet_1 = 0;
    int sub_node = 0;

    if (sel == 0)
        modbus_0_bacnet_1 = 1;
    else
        modbus_0_bacnet_1 = 0;
	if (product_register_value[7] == PM_TSTAT8 || 
        product_register_value[7] == PM_TSTAT_AQ ||
        product_register_value[7] == PM_TSTAT9 || 
        (product_register_value[7] == PM_TSTAT8_WIFI) || 
        (product_register_value[7] == PM_TSTAT8_OCC) || 
        (product_register_value[7] == PM_TSTAT7_ARM) || 
        (product_register_value[7] == PM_TSTAT8_220V)
		)
	{
 
		if (sel == 0)
		{
			protocol = 1;  //改为MSTP
            modbus_0_bacnet_1 = 1;
		} 
		else
		{
			protocol = 0;
            modbus_0_bacnet_1 = 0;
		}
	}
	else
	{
		if (sel == 1)
		{
			protocol = 3;
		}
	}
    if (selected_product_Node.note_parent_serial_number != 0)
        sub_node = 1;
    else
        sub_node = 0;

    
    ChangeDeviceProtocol(modbus_0_bacnet_1, product_register_value[6], 21, protocol, sub_node, g_strCurBuildingDatabasefilePath);
    if((g_protocol == PROTOCOL_MSTP_TO_MODBUS) || (g_protocol == MODBUS_BACNET_MSTP))
        close_bac_com();
    return;
}


void T3000_Default_MainView::OnEnKillfocusEditMstpMac()
{
	CString strTemp;
	m_Editor_macmstp.GetWindowTextW(strTemp);
	int ret = write_one(g_tstat_id, 39, _wtoi(strTemp));
	if (ret > 0)
	{
		product_register_value[39] = _wtoi(strTemp);
	}

 
}


void T3000_Default_MainView::OnCbnKillfocusBaudratecombo()
{

}


BOOL T3000_Default_MainView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			//CWnd *temp_focus=GetFocus();	//Maurice require ,click enter and the cursor still in this edit or combobox.
			////GetDlgItem(IDC_REFRESHBUTTON)->SetFocus();
			//temp_focus->OnKillFocus();
			CWnd *temp_focus = GetFocus();	
			//Maurice require ,click enter and the cursor still in this edit or combobox.
			GetDlgItem(IDC_EDIT_TEST)->SetFocus();
			temp_focus->SetFocus();

			return 1;
		}
	}
	return CFormView::PreTranslateMessage(pMsg);
}

#include "WifiConfigDlg.h"
void T3000_Default_MainView::OnBnClickedButtonWifiConfig()
{
	CWifiConfigDlg dlg;
    //if(selected_product_Node.product_class_id  == PM_TSTAT_AQ)
    //    dlg.SetUI_Type(UI_TYPE_WIFI_REV2);
    //else
        dlg.SetUI_Type(UI_TYPE_WIFI_REV2);
	dlg.DoModal();
}


void T3000_Default_MainView::OnBnClickedCheckPassword()
{
	if (((CButton *)GetDlgItem(IDC_CHECK_PASSWORD))->GetCheck() == 1)
	{
		m_checkpassword = false;
	}
	else
	{
		m_checkpassword = true;
	}
	CString strTemp;

	if (!m_checkpassword)
	{
		m_Edit_AESPassword.SetPasswordChar(NULL);
	
	} 
	else
	{
		m_Edit_AESPassword.SetPasswordChar('*');
		
	}
	m_Edit_AESPassword.Invalidate();
	
}


void T3000_Default_MainView::OnCbnSelchangeComboMrd()
{
	int sel = m_combox_mrd.GetCurSel();
	int write_Value = 0;
	if (product_register_value[7] == PM_TSTAT5i
		|| product_register_value[7] == PM_TSTAT6
		|| product_register_value[7] == PM_TSTAT7
		|| product_register_value[7] == PM_TSTAT8
        || product_register_value[7] == PM_TSTAT9
		|| (product_register_value[7] == PM_TSTAT8_WIFI) || (product_register_value[7] == PM_TSTAT8_OCC) || (product_register_value[7] == PM_TSTAT7_ARM) || (product_register_value[7] == PM_TSTAT8_220V)
		)
	{

		if (sel == 0)
		{
			write_Value = product_register_value[109] & 0xffef;
		}
		else
		{
			write_Value = product_register_value[109] | 0x10;
		}
		int ret = write_one(g_tstat_id, 109, write_Value);
		if (ret > 0)
		{
			product_register_value[109] = write_Value;
		}
	}
	else
	{
		if (sel == 0)
		{
			write_Value = product_register_value[184] & 0xffef;
		}
		else
		{
			write_Value = product_register_value[184] | 0x10;
		}

		int ret = write_one(g_tstat_id, 184, write_Value);
		if (ret > 0)
		{
			product_register_value[184] = write_Value;
		}
	}
}


void T3000_Default_MainView::OnEnKillfocusEditAesEncrypt()
{
	CString str;
	m_Edit_AESPassword.GetWindowTextW(str);
	if (str.GetLength()<=0)
	{
		return;
	}
	unsigned char AESPwd[16];
	memset(AESPwd, 0, 16);
	for (int i = 0;i<str.GetLength();i++)
	{
		AESPwd[i] = str.GetAt(i);
	}
	int ret = Write_Multi_org(g_tstat_id, AESPwd, 600, 16, 5);
	Read_Multi(g_tstat_id, &product_register_value[599], 599, 100);
	if (product_register_value[599] == 0)
	{
		m_Edit_AESPassword.EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PASSWORD)->EnableWindow(FALSE);
	}
	else
	{
		m_Edit_AESPassword.EnableWindow(TRUE);
		m_Edit_AESPassword.SetWindowTextW(GetTextFromReg(600) + GetTextFromReg(604));
		//m_Edit_AESPassword.SetPasswordChar('*');
		((CButton *)GetDlgItem(IDC_CHECK_PASSWORD))->SetCheck(1);
	}
}


void T3000_Default_MainView::OnEnKillfocusEditNetworkid()
{
	CString strTemp;
	m_Edit_Network.GetWindowTextW(strTemp);
	int newid = _wtoi(strTemp);
	write_one(g_tstat_id, 608, newid);
	 
	 
}


void T3000_Default_MainView::OnEnKillfocusEditNodeid()
{
	CString strTemp;
	m_Edit_NodeID.GetWindowTextW(strTemp);
	int newid = _wtoi(strTemp);
	write_one(g_tstat_id, 609, newid);
}


void T3000_Default_MainView::OnEnKillfocusEditFreid()
{
	//strTemp.Format(_T("%d"), (int)product_register_value[608]);
	//m_Edit_Network.SetWindowTextW(strTemp);
	//strTemp.Format(_T("%d"), (int)product_register_value[609]);
	//m_Edit_NodeID.SetWindowTextW(strTemp);
	CString strTemp;
	m_Edit_FrequenceID.GetWindowTextW(strTemp);
	  long Freq = _wtol(strTemp);
	/*long long Freq = ((long long)product_register_value[610]) * 65536 + ((long long)product_register_value[611]);
	*/
	unsigned short FreArray[2];
	  FreArray[0] = Freq / 65536;
	  FreArray[1] = Freq % 65536;
	  Write_Multi_org_short(g_tstat_id, FreArray, 610, 2, 5);
	  
// 	strTemp.Format(_T("%ld"), Freq);
// 	m_Edit_FrequenceID.SetWindowTextW(strTemp);
}


void T3000_Default_MainView::OnEnChangeEditAesEncrypt()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CFormView::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}


void T3000_Default_MainView::OnEnKillfocusEditBacnetDeviceId()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strText;
    GetDlgItemText(IDC_EDIT_BACNET_DEVICE_ID, strText);
    int nValue = _wtoi(strText);
    
    unsigned short temp_high;
    unsigned short temp_low;
    Get_Instance_Reg_Map(product_register_value[7], temp_high, temp_low);


    unsigned int temp_device_id = 0;
    temp_device_id = product_register_value[temp_high] * 65536 + product_register_value[temp_low];
    if (temp_device_id == nValue)	//Add this to judge weather this value need to change.
        return;

    unsigned short temp_device_low;
    unsigned short temp_device_high;
    temp_device_low = nValue % 65536;
    temp_device_high = nValue / 65536;

    int nret_1 = write_one(g_tstat_id, temp_low, temp_device_low, 6);

    int nret_2 = write_one(g_tstat_id, temp_high, temp_device_high, 6);

    if ((nret_1 >= 0) && (nret_2 >= 0))
    {
        product_register_value[temp_low] = temp_device_low;
        product_register_value[temp_high] = temp_device_high;
        SetPaneString(BAC_SHOW_MISSION_RESULTS, _T("Change bacnet device id success"));
    }
    else
    {
        MessageBox(_T("Change bacnet device id failed!"));
    }

}


void T3000_Default_MainView::OnCbnSelchangeBaudratecombo()
{
    // TODO: 在此添加控件通知处理程序代码
    int index_brandrate;
    int brandrate;
    if ((product_register_value[7] == PM_CS_SM_DC) ||
        (product_register_value[7] == PM_CS_SM_AC))
    {
        int n_value = m_brandrate_combox.GetCurSel();	//Add this to judge weather this value need to change.
        if (n_value == 0) // 选中的是9600
        {
            product_register_value[141] = 1;
            brandrate = 9600;
        }
        else
        {
            product_register_value[141] = 0;
            brandrate = 19200;
        }
        int ret = write_one(g_tstat_id, 141, product_register_value[141], 6);

    }
    else
    {
        if (product_register_value[MODBUS_BAUDRATE] == m_brandrate_combox.GetCurSel())	//Add this to judge weather this value need to change.
            return;

        /* Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_BAUDRATE,m_baudRateCombox.GetCurSel(),
        product_register_value[MODBUS_BAUDRATE],this->m_hWnd,IDC_BAUDRATECOMBO,_T("BAUDRATE"));*/

        int ret = write_one(g_tstat_id, MODBUS_BAUDRATE, m_brandrate_combox.GetCurSel());

        index_brandrate = m_brandrate_combox.GetCurSel();
        brandrate = 19200;
        if (index_brandrate == 0)
            brandrate = 9600;
        else if (index_brandrate == 1)
            brandrate = 19200;
        else if (index_brandrate == 2)
            brandrate = 38400;
        else if (index_brandrate == 3)
            brandrate = 57600;
        else if (index_brandrate == 4)
            brandrate = 115200;
        if (GetCommunicationType() == 1)
        {
            return;
        }
    }



    CString SqlText;

    SqlText.Format(_T("update ALL_NODE set Bautrate = '%d' where Serial_ID='%d'"), brandrate, get_serialnumber());
    Change_BaudRate(brandrate);


    CppSQLite3DB SqliteDBBuilding;
    CppSQLite3Table table;
    CppSQLite3Query q;
    SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);

    SqliteDBBuilding.execDML((UTF8MBSTR)SqlText);
    SqliteDBBuilding.closedb();
    CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
    pFrame->ScanTstatInDB();
}
