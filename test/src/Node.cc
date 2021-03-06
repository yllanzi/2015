//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Node.h"
#include "comm.h"
#include <string>


using std::string;
namespace test {

Define_Module(Node);
Node::Node()
{

    timerMsg = NULL;
    blength =10;
    Nbuf[10];

}

void Node::initialize()
{
      timerMsg = new cMessage("timer");
      scheduleAt(simTime(), timerMsg);

      seq = 0;

      //init ָ��
      head = tail =0;//�����ȳ�������ģ��
}

void Node::handleMessage(cMessage *msg)
{
    EV << "HELLO THIS IS NODE, START HANDLING THE TIMERMSG" <<endl;
  ASSERT(msg==timerMsg);
    pkLenBits = &par("pkLenBits");
            txRate = par("txRate");
            sink = simulation.getModuleByPath("sink");
            if (!sink) error("sink not found"); //����Ѱ�ҽڵ�

            int n = seq%10; //define the position of the buffer



          a.data =dblrand()*100;
          a.seq = seq;
 char pkname[40];
                    sprintf(pkname,"this is seq = %d ,and data is %lf",  seq++,a.data);
                    EV << "generating packet " << pkname << endl;
          cPacket *pk = new cPacket( pkname );
           pk->setBitLength(pkLenBits->longValue());
           simtime_t duration = pk->getBitLength() / txRate;
           sendDirect(pk, radioDelay, duration, sink->gate("in"));
//seq++;


 //   EV <<"HELLO ,THIS IS NODE , HANDLE FINISHED " << endl;


    scheduleAt(simTime()+par("sendInterval").doubleValue(),timerMsg);

}
// ��ʼ���ڵ������
NodeBuf Node::newBuf(){
   NodeBuf buf;
   buf.data = 0.0;
   buf.seq = 0;
   return buf;
}

void Node::newData(int  i){
    Nbuf[i].seq = seq;
    double data;
    srand((unsigned)time(NULL));
    Nbuf[i].data = rand();

}
/**
char *Node::setMsg(double data){
    char[10] str ;
    sprintf(str,"%lf",data);
    return *str;
}*/
Data *Node::generateMessage(){
    int src = getIndex();
    Data *newmsg = new Data("data msg");
    newmsg->src = src;
    newmsg->seq = seq;
    newmsg->data = dblrand()*100;
    newmsg->state = 0;
    newmsg->num = 0;
    newmsg->time = 0;
    return newmsg;
}
}; // namespace
