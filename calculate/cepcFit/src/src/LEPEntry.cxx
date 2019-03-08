#include "LEPEntry.h"

ClassImp(LEPError)
ClassImp(LEPEntry)

LEPEntry::LEPEntry( const char* name, const char* unit, const char* mathText )
: _name(name), _mathtext(mathText), _unit(unit), _tot("tot"),_stat("stat"), _syst("syst"), _theo("theo"), _lumi("lumi"),
  _x1(0), _y1(0), 
  _x2(0), _y2(0), 
  _x3(0), _y3(0), 
  _dy(0), 
  _writeResult(false), _scaleResult(0.8), _lineWidth(2),
  _boxSizeStat(0.25), _boxSizeSyst(0.15),_boxSizeTheo(0.3), _boxLineWidth(1.2)
{
  _val=0;
  setStyle();
  setNdigit();
}

TString LEPEntry::name() { return _name; }

LEPEntry::~LEPEntry() {}

void 
LEPEntry::setVal( double val )
{
  _val=val;
}

void 
LEPEntry::setValAndErrors( double val, double stat, double syst, 
			   double theo, double lumi )
{
  setVal(val);
  setStat(stat);
  setSyst(syst);
  setTheo(theo);
  setLumi(lumi);
}

void 
LEPEntry::setTot( double tot )
{
  _tot.asymm=false;
  _tot.lo=tot;
  _tot.hi=tot;
  _tot.status=1;
}

void 
LEPEntry::setStat( double stat )
{
  _stat.asymm=false;
  _stat.lo=stat;
  _stat.hi=stat;
  _stat.status=1;
}

void 
LEPEntry::setSyst( double syst )
{
  _syst.asymm=false;
  _syst.lo=syst;
  _syst.hi=syst;
  _syst.status=1;
}

void 
LEPEntry::setListOfSyst( vector<double> syst )
{
  double syst_(0);
  for( size_t ii=0; ii<syst.size(); ii++ )
    {
      syst_ += pow( syst[ii], 2 );
    }
  setSyst( sqrt( syst_ ) );
}

void 
LEPEntry::setTheo( double theo )
{
  _theo.asymm=false;
  _theo.lo=theo;
  _theo.hi=theo;
  _theo.status=1;
}

void 
LEPEntry::setAsymmTot( double totlo, double tothi )
{
  _tot.asymm=true;
  _tot.lo=totlo;
  _tot.hi=tothi;
  _tot.status=1;
}

void 
LEPEntry::setAsymmStat( double statlo, double stathi )
{
  _stat.asymm=true;
  _stat.lo=statlo;
  _stat.hi=stathi;
  _stat.status=1;
}

void 
LEPEntry::setAsymmSyst( double systlo, double systhi )
{
  _syst.asymm=true;
  _syst.lo=systlo;
  _syst.hi=systhi;
  _syst.status=1;
}

void 
LEPEntry::setAsymmTheo( double theolo, double theohi )
{
  _theo.asymm=true;
  _theo.lo=theolo;
  _theo.hi=theohi;
  _theo.status=1;
}
  
void 
LEPEntry::setLumi( double lumi, bool relative )
{
  double lumi_(lumi);
  if( relative ) lumi_*=_val;
  _lumi.asymm=false;
  _lumi.lo=lumi_;
  _lumi.hi=lumi_;
  _lumi.status=2;
}
  
void 
LEPEntry::setStyle( int marker, double size, int color, 
		    int txtfont, double txtsize, int txtalign, double lineWidth )
{
  _marker   = marker;
  _size     = size;
  _color    = color;
  _txtfont  = txtfont;
  _txtsize  = txtsize;
  _txtalign = txtalign;
  _lineWidth = lineWidth;
  _colorResult = _color;
  _fontResult = _txtfont;
}

TString 
LEPEntry::result()
{
  // special implementation for ATLAS/CMS paper

  char    line_[512];
  TString str_;
  TString pmstr_(" #pm ");
  TString format_("%-4.");
  format_ += _ndigit;
  format_ += "f";
  TString  valstr_;
  TString totstr_;
  TString statstr_;
  TString syststr_;
  TString theostr_;
  TString lumistr_;

  sprintf( line_, format_.Data(), _val );
  valstr_ = line_;
  str_ = valstr_;

  sprintf( line_, format_.Data(), _tot.lo );
  totstr_ = line_;
  str_ = str_ + pmstr_;
  str_ += totstr_;

  str_ += " (";

  sprintf( line_, format_.Data(), _stat.lo );
  statstr_ = line_;
  str_ = str_ + pmstr_;
  str_ += statstr_;

  sprintf( line_, format_.Data(), _syst.lo );
  syststr_ = line_;
  str_ = str_ + pmstr_;
  str_ += syststr_;

  str_ += " )";
  str_ += " ";

  str_ += _unit;

  return str_;
}

void
LEPEntry::draw()
{
  // special implementation for ATLAS/CMS paper

  double  xval_[1];
  double  yval_[1];
  double    ey_[1];
  double etotlo_[1];
  double etothi_[1];
  
  xval_[0] = _val;
  yval_[0] = _y1;
  ey_[0] = 0;
  etotlo_[0] = _tot.lo;
  etothi_[0] = _tot.hi;

  double x0_, y0_, x1_, y1_;

  TMarker marker_;
  marker_.SetMarkerStyle( _marker );
  marker_.SetMarkerSize( _size );
  marker_.SetMarkerColor( _color );

  TBox box_;

  if( _stat.ok() )
    {
      x0_ = xval_[0]-_stat.lo;
      x1_ = xval_[0]+_stat.hi;
      y0_ = yval_[0]-_boxSizeStat; 
      y1_ = yval_[0]+_boxSizeStat;   
      box_.SetFillStyle(1001);
      box_.SetFillColor(kYellow-10);
      box_.DrawBox(x0_, y0_, x1_, y1_ );
      box_.SetFillStyle(0);
      box_.SetLineColor(kOrange-3);
      box_.SetLineWidth(_boxLineWidth);
      box_.DrawBox(x0_, y0_, x1_, y1_ );
    }
      
  if( _syst.ok() )
    {
      x0_ = xval_[0]-_syst.lo;
      x1_ = xval_[0]+_syst.hi;
      y0_ = yval_[0]-_boxSizeSyst; 
      y1_ = yval_[0]+_boxSizeSyst; 

      box_.SetFillStyle(1001);
      box_.SetFillColor(kMagenta-9);
      box_.DrawBox(x0_, y0_, x1_, y1_ );
      box_.SetFillStyle(0);
      box_.SetLineColor(kMagenta);
      box_.SetLineWidth(_boxLineWidth);
      box_.DrawBox(x0_, y0_, x1_, y1_ );
    }

  if( _theo.ok() )
    {
      x0_ = xval_[0]-_theo.lo;
      x1_ = xval_[0]+_theo.hi;
      y0_ = yval_[0]-_boxSizeTheo;
      y1_ = yval_[0]+_boxSizeTheo;

      box_.SetFillStyle(1002);
      box_.SetFillColor(kAzure+7);
      box_.DrawBox(x0_, y0_, x1_, y1_ );
    }
  
  if( _tot.ok() )
    {
      TGraphAsymmErrors gstat_( 1, xval_, yval_, etotlo_, etothi_, ey_, ey_ );
      gstat_.SetMarkerSize( 0 );
      gstat_.SetLineColor( kBlack );
      gstat_.SetLineWidth( _lineWidth );
      gstat_.DrawClone("Same");
      marker_.DrawMarker( _val, _y1 );
    }

  TString str_ = result();

  TLatex latex;  
  // TMathText latex;
  latex.SetTextFont(_txtfont);
  latex.SetTextSize(_txtsize);    
  latex.SetTextAlign(_txtalign); 
  latex.DrawLatex(_x1,_y1+_dy,_name);
  // latex.DrawMathText(_x1,_y1+_dy,_name);
  if( _writeResult )
    {
      int sng_ = +1;
      if( _y2==0 ) 
	{
	  _x2 = _x1;
	  _y2 = _y1;
	  sng_ = -1;
	}
      latex.SetTextSize(_scaleResult*_txtsize);    
      latex.SetTextAlign(_txtalign); 
      latex.SetTextFont(_fontResult); 
      latex.SetTextColor(_colorResult); 
      latex.DrawLatex(_x2,_y2+sng_*_dy,str_);
      // latex.DrawMathText(_x2,_y2+sng_*_dy,str_);
    }

  if( _mathtext!=0 )
    {
      TMathText math;
      math.SetTextSize( _txtsize);    
      math.SetTextAlign(_txtalign); 
      math.DrawMathText(_x3,_y3,_mathtext);
    }

}


