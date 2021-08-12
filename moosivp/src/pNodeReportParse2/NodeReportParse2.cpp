/************************************************************/
/*    NAME: Arjun Gupta                                              */
/*    ORGN: MIT                                             */
/*    FILE: NodeReportParse2.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "NodeReportParse2.h"

using namespace std;

//---------------------------------------------------------
// Constructor

NodeReportParse2::NodeReportParse2()
{
}

//---------------------------------------------------------
// Destructor

NodeReportParse2::~NodeReportParse2()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool NodeReportParse2::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
    if(key == "NODE_REPORT")
      ProcessNodeReport(sval);
    else
      reportRunWarning("Unhandled Mail: " + key);
   }	
   return(true);
}

//---------------------------------------------------------
//Procedure: ProcessNodeReport
//Function: Takes in a node report and then sends it back out with the source name appended

void NodeReportParse2::ProcessNodeReport(string report)
{
  string val= report;
  /*/ Get vehicle name 
  string name= parseStringQ(val,',')[0];
  biteStringX(name,'=');
  for(int i = 0; i < name.size(); i++) {
    name.at(i) = toupper(name.at(i));
  }*/

  // Get vehicle name
  string name = toupper(tokStringParse(val, "NAME", ',', '='));

  // Get vehicle coords
  double x = tokDoubleParse(val, "X", ',', '=');
  double y = tokDoubleParse(val, "Y", ',', '=');

  Notify("NAV_"+name+"_X", x);
  Notify("NAV_"+name+"_Y", y);

  reportEvent("Reposted node report to: NAV_"+name+"_X="+doubleToString(x)+"and NAV_"+name+"_Y="+doubleToString(y));
}
//---------------------------------------------------------
// Procedure: OnConnectToServer

bool NodeReportParse2::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool NodeReportParse2::Iterate()
{
  AppCastingMOOSApp::Iterate();
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool NodeReportParse2::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = toupper(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "FOO") {
      handled = true;
    }
    else if(param == "BAR") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void NodeReportParse2::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("NODE_REPORT", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool NodeReportParse2::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "File:                                        \n";
  m_msgs << "============================================ \n";

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString();

  return(true);
}




