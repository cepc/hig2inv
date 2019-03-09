#ifndef ROOT_LEPEntry
#define ROOT_LEPEntry

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

#include "TFile.h"
#include "TH1F.h"
#include "TString.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMathText.h"
#include "TStyle.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TMarker.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TBox.h"
#include "TPolyLine.h"

using namespace std;

class LEPError
{
  TString _name;

public:

  double lo;
  double hi;
  bool  asymm;
  int   status;  // 0:inactive; 1:in-quadrature; 2:linearly

  void setName( const char* name ) { _name=name; } 
  TString name() const { return _name; }
  double err() const 
  {
    if( status==0 ) return 0;
    if( asymm ) return 0.5*(lo+hi);
    return lo;
  }
  bool ok() const { return status>0; }
  double errlo() const 
  {
    if( status==0 ) return 0;
    return lo;
  }
  double errhi() const 
  {
    if( status==0 ) return 0;
    return hi;
  }
  
  LEPError( const char* name, double err=0 ) 
    : _name(name), lo(err), hi(err), asymm(false), status(0) {}
  LEPError( const char* name, double errlo, double errhi ) 
    : _name(name), lo(errlo), hi(errhi), asymm(true), status(0) {}
  ~LEPError() {}
  ClassDef(LEPError,1);
};


class LEPEntry
{
private:

  TString    _name;
  TString    _mathtext;
  TString    _unit;
  double        _val;
  LEPError _tot;
  LEPError _stat;
  LEPError _syst;
  LEPError _theo;
  LEPError _lumi;

  int    _ndigit;

  int     _marker;
  double      _size;
  int       _color;

  int     _txtfont;
  double   _txtsize;
  double _txtalign;

  double _x1, _y1;
  double _x2, _y2;
  double _x3, _y3;
  double _dy;

  bool    _writeResult;
  double   _scaleResult;
  int        _fontResult;
  int      _colorResult;

  double _lineWidth;

  double _boxSizeStat;
  double _boxSizeSyst;
  double _boxSizeTheo;
  double _boxLineWidth;
  
public:

  LEPEntry( const char* name=0, const char* unit=0, const char* mathText=0 );
  ~LEPEntry();

  void setVal( double val=0 );
  void setValAndErrors( double val=0, double stat=0, double syst=0, 
			double theo=0, double lumierror=0.11 );
  void setTot( double tot );
  void setStat( double stat );
  void setSyst( double syst );
  void setListOfSyst( vector<double> syst );
  void setTheo( double theo );
  void setLumi( double lumi, bool relative=true );
  void setAsymmTot( double totlo, double totup );
  void setAsymmStat( double statlo, double statup );
  void setAsymmSyst( double systlo, double systup );
  void setAsymmTheo( double theolo, double theoup );
  void setNdigit( int ndigit=3 ) { _ndigit = ndigit; }
  void setStyle( int marker=kFullCircle, double size=0.8, int color=kBlack, 
		 int txtfont=42, double txtsize=0.8, int txtalign=11,
		 double lineWidth=2 );
  void setResultStyle( int color=kBlack, int txtfont=42 ) { _colorResult = color; _fontResult = txtfont; }

  void setX( double x1, double x2=0 ) { _x1=x1; _x2=x2; }
  void setY( double y1, double y2=0 ) { _y1=y1; _y2=y2; }
  void setXYMath( double x3, double y3 ) { _x3=x3; _y3=y3; }
  void setDY( double dy ) { _dy=dy; }
  void setStatName( const char* name ) { _stat.setName(name); }
  void setSystName( const char* name ) { _syst.setName(name); }
  void setTheoName( const char* name ) { _theo.setName(name); }
  void setLumiName( const char* name ) { _lumi.setName(name); }
  void setScale( double scale ) { _scaleResult=scale; }
  void setStatBoxSize(double size) {_boxSizeStat=size;}
  void setSystBoxSize(double size) {_boxSizeSyst=size;}
  void setTheoBoxSize(double size) {_boxSizeTheo=size;}
  void setBoxLineWidth(double width) {_boxLineWidth=width;}
  void writeResult( int yes=1 ) 
  { 
    if( yes ) _writeResult=true; 
    else      _writeResult=false; 
  }

  TString name();
  TString result();

  void draw();
  ClassDef(LEPEntry,1);
};

#endif
