#pragma once



// CBacnetThirdPartyMain ������ͼ

class CBacnetThirdPartyMain : public CFormView
{
	DECLARE_DYNCREATE(CBacnetThirdPartyMain)

protected:
	
	

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BACNET_THIRD_PARTY_MAIN };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CBacnetThirdPartyMain();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
    virtual ~CBacnetThirdPartyMain();
    void Fresh();
};

