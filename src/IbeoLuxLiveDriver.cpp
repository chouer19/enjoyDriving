//======================================================================
/*! \file IbeoSdkLuxDriver.cpp
 * \copy from file IbeoSdkLuxLiveDemo.cpp
 *
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date Jun 20, 2019
 *
 * project for connecting to a LUX and process the received
 * data blocks.
 *///-------------------------------------------------------------------

// ibeo headers
#include <ibeosdk/lux.hpp>
#include <ibeosdk/IpHelper.hpp>

#include <ibeosdk/datablocks/commands/CommandLuxReset.hpp>
#include <ibeosdk/datablocks/commands/CommandLuxGetStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandLuxGetParameter.hpp>
#include <ibeosdk/datablocks/commands/CommandLuxSetParameter.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>
#include <ibeosdk/datablocks/commands/ReplyLuxGetStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyLuxGetParameter.hpp>
#include <ibeosdk/datablocks/commands/CommandLuxSetNtpTimestampSync.hpp>
#include "ibeosdk/Time.hpp"

// protobuf headers
#include "msgs/Ibeo.pb.h"
#include "msgs/Geometry.pb.h"

// zmq headers
#include "zmq/zhelpers.hpp"

//
#include <iostream>
#include <cstdlib>

//======================================================================

using namespace ibeosdk;

//======================================================================

const ibeosdk::Version::MajorVersion majorVersion(5);
const ibeosdk::Version::MinorVersion minorVersion(2);
const ibeosdk::Version::Revision revision(2);
const ibeosdk::Version::PatchLevel patchLevel;
const ibeosdk::Version::Build build;
const std::string info = "IbeoSdkLuxLiveDriver";

ibeosdk::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);
IbeoSDK ibeoSDK;

//======================================================================

void live_demo(LogFileManager& logFileManager, std::string ip);

//======================================================================

void convertObjLuxListToProtobuf(const ObjectListLux* const pObj, Ibeo_msg::ObjectLuxList &protoObjList);

//=======================================================================
TimeConversion tc;

//======================================================================
    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);

class AllLuxListener : public ibeosdk::DataListener<ObjectListLux>,
                       public ibeosdk::DataListener<LogMessageError>,
                       public ibeosdk::DataListener<LogMessageDebug>,
                       public ibeosdk::DataListener<LogMessageNote>,
                       public ibeosdk::DataListener<LogMessageWarning> {
public:
	virtual ~AllLuxListener() {}

public:
	//========================================
	virtual void onData(const LogMessageError* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
				<< "LogMessage (Error) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
	//========================================
	virtual void onData(const LogMessageWarning* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
				<< "LogMessage (Warning) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
	//========================================
	virtual void onData(const LogMessageNote* const logMsg)
	{
	//	logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
	//			<< "LogMessage (Note) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
	//========================================
	virtual void onData(const LogMessageDebug* const logMsg)
	{
	//	logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
	//			<< "LogMessage (Debug) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	void onData(const ObjectListLux* const pObj)
	{
		logInfo << "Objects received: # " << pObj->getNumberOfObjects() << std::endl;
                Ibeo_msg::ObjectLuxList protoObjList;
                convertObjLuxListToProtobuf(pObj, protoObjList);
                std::string buff;
                protoObjList.SerializeToString(&buff);
                //publish thecontrolm to all
                s_sendmore (publisher, "ibeoLuxObjList");
                s_send (publisher, buff);
	}
}; // AllLuxListener


//======================================================================
// Data:2019.01.22
// Author: XueCHong
// Description:
// * convert objLuxList to protobuf msgs
// *************************************
void convertObjLuxListToProtobuf(const ObjectListLux* const pObj, Ibeo_msg::ObjectLuxList &protoObjList){
    protoObjList.clear_objects();
    protoObjList.set_numberofobjects(pObj->getNumberOfObjects());
    for(int i=0;i < pObj->getNumberOfObjects();i++){
        std::cout << "object ID:" << pObj->getObjects()[i].getObjectId();
        Ibeo_msg::ObjectLux* obj = protoObjList.add_objects();
        obj->set_objectid(pObj->getObjects()[i].getObjectId());
        obj->set_objectage(pObj->getObjects()[i].getObjectAge());
        obj->set_predictionage(pObj->getObjects()[i].getPredictionAge());
        obj->set_relativetimestamp(pObj->getObjects()[i].getRelativeTimestamp());
        // reference point
        Geometry_msg::Point2d* objPoint;
        //Geometry_msg::Point2d* objPoint = obj->mutable_referencepoint();
        objPoint = obj->mutable_referencepoint();
        objPoint->set_posx(pObj->getObjects()[i].getReferencePoint().getX());
        objPoint->set_posy(pObj->getObjects()[i].getReferencePoint().getY());

        // refrence point sigma
        Geometry_msg::PointSigma2d* objPointSigma;
        objPointSigma = obj->mutable_referencepointsigma();
        objPointSigma->set_sigmax(pObj->getObjects()[i].getReferencePointSigma().getX());
        objPointSigma->set_sigmay(pObj->getObjects()[i].getReferencePointSigma().getY());

        // closest point
        objPoint = obj->mutable_closestpoint();
        objPoint->set_posx(pObj->getObjects()[i].getClosestPoint().getX());
        objPoint->set_posy(pObj->getObjects()[i].getClosestPoint().getY());

        // Bounding box center
        objPoint = obj->mutable_boundingboxcenter();
        objPoint->set_posx(pObj->getObjects()[i].getBoundingBoxCenter().getX());
        objPoint->set_posy(pObj->getObjects()[i].getBoundingBoxCenter().getY());

        obj->set_boundingboxwidth(pObj->getObjects()[i].getBoundingBoxWidth());
        obj->set_boundingboxlength(pObj->getObjects()[i].getBoundingBoxLength());

        // Object box center
        objPoint = obj->mutable_objectboxcenter();
        objPoint->set_posx(pObj->getObjects()[i].getObjectBoxCenter().getX());
        objPoint->set_posy(pObj->getObjects()[i].getObjectBoxCenter().getY());

        obj->set_objectboxsizex(pObj->getObjects()[i].getObjectBoxSizeX());
        obj->set_objectboxsizey(pObj->getObjects()[i].getObjectBoxSizeY());
        obj->set_objectboxorientation(pObj->getObjects()[i].getObjectBoxOrientation());

        // Absolute velocity
        objPoint = obj->mutable_absolutevelocity();
        objPoint->set_posx(pObj->getObjects()[i].getAbsoluteVelocity().getX());
        objPoint->set_posy(pObj->getObjects()[i].getAbsoluteVelocity().getY());

        //
        obj->set_absolutevelocitysigmax(pObj->getObjects()[i].getAbsoluteVelocitySigmaX());
        obj->set_absolutevelocitysigmay(pObj->getObjects()[i].getAbsoluteVelocitySigmaY());

        //
        switch(pObj->getObjects()[i].getClassification()){
            case luxObjectClass::LuxObjectClass_Unclassified:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Unclassified);
                break;
            }
            case luxObjectClass::LuxObjectClass_UnknownSmall:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_UnknownSmall);
                break;
            }
            case luxObjectClass::LuxObjectClass_UnknownBig:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_UnknownBig);
                break;
            }
            case luxObjectClass::LuxObjectClass_Pedestrian:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Pedestrian);
                break;
            }
            case luxObjectClass::LuxObjectClass_Bike:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Bike);
                break;
            }
            case luxObjectClass::LuxObjectClass_Car:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Car);
                break;
            }
            case luxObjectClass::LuxObjectClass_Truck:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Truck);
                break;
            }
            case luxObjectClass::LuxObjectClass_Bicycle:{
                obj->set_classification(Ibeo_msg::ObjectLux::LuxObjectClass_Bicycle);
                break;
            }
            default:{
                break;
            }
        }

        obj->set_classificationage(pObj->getObjects()[i].getClassificationAge());
        obj->set_classificationcertainty(pObj->getObjects()[i].getClassificationCertainty());

        obj->set_numberofcontourpoints(pObj->getObjects()[i].getNumberOfContourPoints());

        for(int j = 0; j < obj->numberofcontourpoints() ; j++){
            Geometry_msg::Point2d* point = obj->add_contourpoints();
            point->set_posx(pObj->getObjects()[i].getContourPoints()[j].getX());
            point->set_posy(pObj->getObjects()[i].getContourPoints()[j].getY());
        }
    }
    NTPTime nptTime = NTPTime();
    nptTime.setFromPTime(Time::localTime());
    protoObjList.set_timestamp(nptTime.getMilliseconds());
}
//======================================================================

int checkArguments(const int argc, const char** argv, bool& hasLogFile)
{
	const int minNbOfNeededArguments = 2;
	const int maxNbOfNeededArguments = 3;

	bool wrongNbOfArguments = false;
	if (argc < minNbOfNeededArguments) {
		std::cerr << "Missing argument" << std::endl;
		wrongNbOfArguments = true;
	}
	else if (argc > maxNbOfNeededArguments) {
		std::cerr << "Too many argument" << std::endl;
		wrongNbOfArguments = true;
	}

	if (wrongNbOfArguments) {
		std::cerr << argv[0] << " " << " IP [LOGFILE]" << std::endl;
		std::cerr << "\tIP is the ip address of the LUX sensor, e.g. 192.168.0.1." << std::endl;
		std::cerr << "\tLOGFILE name of the log file. If ommitted, the log output will be performed to stderr." << std::endl;
		return 1;
	}

	hasLogFile = (argc == maxNbOfNeededArguments);
	return 0;
}

//======================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	bool hasLogFile;
	const int checkResult = checkArguments(argc, argv, hasLogFile);
	if (checkResult != 0)
		exit(checkResult);
	int currArg = 1;

	std::string ip = argv[currArg++];

	const off_t maxLogFileSize = 1000000;

	LogFileManager logFileManager;
	ibeosdk::LogFile::setTargetFileSize(maxLogFileSize);

	if (hasLogFile) {
		ibeosdk::LogFile::setLogFileBaseName(argv[currArg++]);
	}
	const ibeosdk::LogLevel ll = ibeosdk::logLevelFromString("Debug");
	ibeosdk::LogFile::setLogLevel(ll);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
		        << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	live_demo(logFileManager, ip);

	exit(0);
}

//======================================================================

void live_demo(LogFileManager& logFileManager, std::string ip)
{
    // prepare publisher first
    publisher.bind("tcp://*:5563");

	AllLuxListener allLuxListener;
	const uint16_t port = getPort(ip, 12002);
	IbeoLux lux(ip, port);
	lux.setLogFileManager(&logFileManager);

	lux.registerListener(&allLuxListener);

	lux.getConnected();

	// Just to keep the program alive
	while (true) {
		if (!lux.isConnected())
			return;
#		ifdef _WIN32
			::Sleep(1);
#		else // _WIN32
			sleep(1);
#ifdef WITHCOMMANDDEMO

			//CommandLuxReset resetCmd;
			{
				CommandLuxGetStatus getStatus;
				ReplyLuxGetStatus replyStatus;
				logInfo << "========================" << std::endl;
				logInfo << "Send Command GetStatus" << std::endl;
				logInfo << "------------------------" << std::endl;
				lux.sendCommand(getStatus, replyStatus);
				logError << "### Status: " << replyStatus.toString() << std::endl;
			}
			{
				CommandLuxGetParameter getParam(ParameterIndex(0x1200));
				ReplyLuxGetParameter replyParam;
				logInfo << "========================" << std::endl;
				logInfo << "Send Command getParam MPX" << std::endl;
				logInfo << "------------------------" << std::endl;
				lux.sendCommand(getParam, replyParam);
				logError << "### SENSORMOUNTING_X: " << int16_t(replyParam.getParameterData()) << std::endl;
			}
			{
				logInfo << "========================" << std::endl;
				logInfo << "Send Command setParam MPX" << std::endl;
				logInfo << "------------------------" << std::endl;
				CommandLuxSetParameter setParam(ParameterIndex(0x1200), ParameterData(1500));
				ReplyLuxSetParameter replySetParam;
				lux.sendCommand(setParam, replySetParam);
			}
			{
				logInfo << "========================" << std::endl;
				logInfo << "Send Command getParam MPX" << std::endl;
				logInfo << "------------------------" << std::endl;
				CommandLuxGetParameter getParam(ParameterIndex(0x1200));
				ReplyLuxGetParameter replyParam;				lux.sendCommand(getParam, replyParam);
				logError << "### SENSORMOUNTING_X: " << int16_t(replyParam.getParameterData()) << std::endl;
			}
			{
				logInfo << "========================" << std::endl;
				logInfo << "Send Command timeSync" << std::endl;
				logInfo << "------------------------" << std::endl;
				logError << "### Current time: " << Time::localTime() << std::endl;
				CommandLuxSetNtpTimestampSync timeSync(NTPTime(Time::localTime()));
				ReplyLuxSetNTPTimestampSync syncReply;
				lux.sendCommand(timeSync, syncReply);
			}
			logError << "========================================================" << std::endl << std::endl;
#endif // WITHCOMMANDDEMO
#               endif // _WIN32
	}
}

//======================================================================
