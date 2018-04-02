// -*- C++ -*- //
//
// Description: Higgs -> Invisible 
//
// Original Author:  JING Maoqiang <jingmq@ihep.ac.cn>
//         Created:  [2018-04-02 Mon 15:49] 
//         Inspired by CHEN Zhenxing's code 
//
//

#include <marlin/Processor.h>

class hig2inv  : public marlin::Processor
{
	public:

		Processor*  newProcessor() { return new hig2inv ; }

		hig2inv();

		~hig2inv() {};

		void init();

		void processEvent( );

		void end();

};


//
// system include files
//

hig2inv::hig2inv()
     : Processor("hig2inv")
{

}

void hig2inv::init() {


}

void hig2inv::processEvent( ) 
{	

}	

void hig2inv::end()
{

}
