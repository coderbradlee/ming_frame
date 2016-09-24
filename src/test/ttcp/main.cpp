#include "common.h"
int main(int argc,char* argv[])
{
	Options op;
	if(parseCommandLine(argc,argv,&op))
	{
		if(op.transmit)
		{
			transmit(op);
		}
		else if(op.receive)
		{
			receive(op);
		}
		else
		{
			//assert(0);
		}
	}
	return 0
}