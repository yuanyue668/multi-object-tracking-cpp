/*
 * byavs.h
 *
 *  Created on: 2019年4月30日
 *      Author: Dell
 */

#ifndef TOOLS_SO_INCLUDE_BYAVS_API_H_
#define TOOLS_SO_INCLUDE_BYAVS_API_H_
#include <opencv2/core/core.hpp>
#include <vector>
#include <stdlib.h>
#include <memory>
typedef struct BboxInfo
{
  int topLeftX;
  int topLeftY;
  int width;
  int height;
}BboxInfo;

typedef struct {
  float confidence;
  int minWidth;
  int minHeight;
  int maxWidth;
  int maxHeight;
} BasicDetectParas;
typedef std::vector<cv::Mat> ImgBGRArray;

/**
 * @brief The Detector class
 * Input:ImgBGRArray
 * Output:objArray
 * Batch can be adjusted freely
 */
typedef struct {
  BasicDetectParas detectPara;
  //Other required parameters can be added.
} DetectParas;

typedef struct
{
  int label;
  float score;
  BboxInfo box;
} DetectObject;

typedef std::vector<DetectObject> DetectObjects;
typedef std::vector<DetectObjects> ObjArray;
class Detector
{
public:
  // init detector
  bool init(const std::string& model_dir, const DetectParas& pas, const int gpu_id);

  //img inference
  bool inference(const ImgBGRArray& imgBGRs, ObjArray& objects);

  //detector release
  void release();

private:
    void * detector;
};



/**
 * @brief The face Detector class
 * Input:ImgBGRArray
 * Output:FaceObjArray
 */
typedef struct {
  BasicDetectParas detectPara;
  //Other required parameters can be added.
} FaceDetectParas;

typedef struct
{
  float score;
  BboxInfo box;
} FaceDetectObject;

typedef std::vector<FaceDetectObject> FaceDetectObjects;
typedef std::vector<FaceDetectObjects> FaceObjArray;

class FaceDetector
{
public:
  // init detector
  bool init(const std::string& model_dir, const FaceDetectParas& pas, const int gpu_id);

  //img inference
  bool inference(const ImgBGRArray& imgBGRs, FaceObjArray& objects);

  //detector release
  void release();
private:
  void * detector;
};



/**
 * @brief The plate Detector class
 * Input:ImgBGRArray
 * Output:MarkObjArray
 */
typedef struct {
  BasicDetectParas detectPara;
  //Other required parameters can be added.
} MarkDetectParas;

typedef struct
{
  int label;//0-车牌 、1-人(驾驶员和副驾驶)、2-年检标、3-后视镜、4-车大灯、5-中控摆件、6-遮阳板、7-挂饰、8-车窗
  float score;
  BboxInfo box;
} MarkDetectObject;
typedef std::vector<MarkDetectObject> MarkDetectObjects;
typedef std::vector<MarkDetectObjects> MarkObjArray;
class MarkDetector //标志物检测器(车牌、挂件、摆件等9中检测目标)
{
public:
  // init markDetector
  bool init(const std::string& model_dir, const MarkDetectParas& pas, const int gpu_id);

  //markDetector inference
  bool inference(const ImgBGRArray& imgBGRs, MarkObjArray& objects);

  //markDetector release
  void release();
private:
    void * detector;
};



/**
 * @brief The MultiTracker class
 * Input1:cv::Mat
 * Input2:detectObjects
 * Output:std::vector<TrackeKeyObject>
 */
typedef struct {
    //The parameters of MultiTracker.

} TrackeParas;

typedef struct {
    int label;
    BboxInfo box;  // key box
    cv::Mat img; // full image corresponding to the optimal frame
} TrackeKeyObject;

typedef struct {
    int id;
    int label;
    BboxInfo box;
    cv::Mat img;
    bool return_state;
} TrackingObjects;

class MultiTracker;

class MultipleTracker;

class MultipleTracking{
public:
   bool init(const std::string& model_dir, const TrackeParas& pas, const int gpu_id);
   bool inference(const cv::Mat& imgBGR, const DetectObjects& detectResults, std::vector<TrackeKeyObject>& keyObjects);
   bool inference(const cv::Mat& imgBGR, const DetectObjects& detectResults, std::vector<TrackingObjects>& keyObjects);
   void release();
private:
   void*  trackingPtr;
};


class Tracking{
public:
   bool init(const std::string& model_dir, const TrackeParas& pas, const int gpu_id);
   bool inference(const cv::Mat& imgBGR, const DetectObjects& detectResults, std::vector<TrackeKeyObject>& keyObjects);
   bool inference(const cv::Mat& imgBGR, const DetectObjects& detectResults, std::vector<TrackingObjects>& keyObjects);
   void release();
private:
   void*  trackingPtr;
};



/**
 * @brief The VehicleRecognizer class
 * Input:ImgBGRArray
 * Output:vehAttrArray
 */
typedef struct {
    //The parameters of VehicleRecognizer.
} VehParas;

typedef struct VehicleAttr
{
  char vehicleSide:2;//0-车头、1-车尾、2-侧身
  char vehicleCategory:5;//0-轿车、1-越野车、2-商务车（mpv）、3-小型货车、4-大型货车、5-轻客、6-小型客车、7-大型客车、8-三轮车、9-微面、10-皮卡车、11-挂车、12-混凝土搅拌车、13-罐车、14-随车吊、15-消防车、16-渣土车、17-押运车、18-工程抢修车、19-救援车、20栏板卡车
  char vehicleColor:4;//0-黑色、1-蓝色、2-棕色、3-绿色、4-灰色、5-白色、6-红色、7-黄色、8-粉色、9-紫色、10-青色、11-深灰色、12-金色
  bool annualInspecStandard;//无年检标、有年检标
  bool pendant;//无挂件、有挂件
  bool decoration;//无摆件、有摆件
  bool driverSafetyBelt;//有系安全带、无系安全带
  bool copilotSafetyBelt;//副驾驶 有系安全带、无系安全带
  bool tissueBox; //有纸巾盒、无纸巾盒
  bool driverPhone;//主驾驶打电话 有、无
  bool sunShield; //打开遮阳板、未打开遮阳板
  bool skylightPeople;//天窗站人 有、无
  unsigned int  vehicleBrand;//车辆品牌，数字类型，需要提供品牌对照表
} VehAttr;
typedef std::vector<VehAttr> VehAttrArray;
class VehicleStructured {
public:
    // init Vehicle Recognizer
    bool init(const std::string& model_dir, const VehParas& pas, const int gpu_id);

    //Vehicle Recognizer inference 因为需要使用标志物检测进行再次分析，所以输入加入标志物检测结果
    bool inference(const ImgBGRArray& imgs, const MarkObjArray& markObj, VehAttrArray& vehOut);

    //Vehicle Recognizer release
    void release();
};



/**
 * @brief The PersonRecognizer class
 */

typedef struct {
    //The parameters of VehicleRecognizer.
} PedParas;

typedef struct PedestrainAttr
{
  // char hairstyle:3;//0-未知、1-短发、2-马尾、3-盘发、4-头部被遮挡、5-长发、6-光头
  // char ageGroup:3;//0-未知、1-幼儿、2-少年、3-青年、4-中年、5-老年
  // char upperCategory:4;//0-马甲吊带背心、1-衬衫、2-西服、3-毛衣、4-皮衣夹克、5-羽绒服、6-大衣风衣、7-连衣裙、8-T恤、9-无上衣、10-其它
  // char upperTexture:3;//0-纯色、1-碎花、2-条纹、3-格子、4-文字、5-其他
  // char upperColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  // char lowerCategory:3;//0-长裤、1-七分裤、2-长裙、3-短裙、4-短裤、5-连衣裙
  // char lowerColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  // char shoesCategory:3;//0-未知、1-光脚,2-皮鞋、3-运动鞋、4-靴子、5-凉鞋、6-休闲鞋、7-其他
  // char shoesColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  // char bagCategory:2;//0-单肩包、1-双肩包、2-挎包、3-其他
  // char holdBaby:2;//0-抱小孩、1-背小孩、3-其他
  // char hasHandItems:2;//0-无手持物、1-有单个手持物 、 2-有多个手持物
  // char handItems:3;//0-手机、1-手拎包、2-拉杆箱、3-水杯、4-婴儿车、5-购物袋、6-其他
  // char hatType:2;//0-帽子、1-头盔、2-未戴帽子
  // char hatColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  // char orientation:2;//0-正向、1-侧身、2-背部
  // char posture:2;//0-胖、1-瘦、2-中
  // char racial:2;//0-汉族、1-维族、2-黑人、3-白人
  // char pedHeight:2;//0-高、1-中、2-低
  // bool hasUmbrella;//有打伞、无打伞
  // bool holdPhone;//手持接打电话、未接打电话
  // bool hasScarf;//有围巾、无围巾
  // bool gender;//ture-男、false-女
  // bool hasGlasses;//带眼镜  不带眼镜
  // bool hasMask;//戴口罩  不带口罩
  // bool hasBag;//有背包、无背包
  // bool hasBaby;//有小孩、无小孩

  
  char hairstyle;//0-未知、1-短发、2-马尾、3-盘发、4-头部被遮挡、5-长发、6-光头
  char ageGroup;//0-未知、1-幼儿、2-少年、3-青年、4-中年、5-老年
  char upperCategory;//0-马甲吊带背心、1-衬衫、2-西服、3-毛衣、4-皮衣夹克、5-羽绒服、6-大衣风衣、7-连衣裙、8-T恤、9-无上衣、10-其它
  char upperTexture;//0-纯色、1-碎花、2-条纹、3-格子、4-文字、5-其他
  char upperColor;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char lowerCategory;//0-长裤、1-七分裤、2-长裙、3-短裙、4-短裤、5-连衣裙
  char lowerColor;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char shoesCategory;//0-未知、1-光脚,2-皮鞋、3-运动鞋、4-靴子、5-凉鞋、6-休闲鞋、7-其他
  char shoesColor;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char bagCategory;//0-单肩包、1-双肩包、2-挎包、3-其他
  char holdBaby;//0-抱小孩、1-背小孩、3-其他
  char hasHandItems;//0-无手持物、1-有单个手持物 、 2-有多个手持物
  char handItems;//0-手机、1-手拎包、2-拉杆箱、3-水杯、4-婴儿车、5-购物袋、6-其他
  char hatType;//0-帽子、1-头盔、2-未戴帽子
  char hatColor;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char orientation;//0-正向、1-侧身、2-背部
  char posture;//0-胖、1-瘦、2-中
  char racial;//0-汉族、1-维族、2-黑人、3-白人
  char pedHeight;//0-高、1-中、2-低
  bool hasUmbrella;//有打伞、无打伞
  bool holdPhone;//手持接打电话、未接打电话
  bool hasScarf;//有围巾、无围巾
  bool gender;//ture-男、false-女
  bool hasGlasses;//带眼镜  不带眼镜
  bool hasMask;//戴口罩  不带口罩
  bool hasBag;//有背包、无背包
  bool hasBaby;//有小孩、无小孩
} PedestrainAttr;
typedef std::vector<PedestrainAttr> PedAttrArray;
class PersonStructured {
public:
    // init
    bool init(const std::string& model_dir, const PedParas& pas, const int gpu_id);
    // inference
    bool inference(const ImgBGRArray& imgs, PedAttrArray& pedOut);
    //
    void release();
private:
  void* model;

};



/**
 * @brief The nonVehicleRecognizer class
 * Input:ImgBGRArray
 * Output:nonVehAttrArray
 */
typedef struct {
    //The parameters of nonVehicleRecognizer.
} NonVehParas;

typedef struct NonVehicle
{
  char hairstyle:3;//0-未知、1-短发、2-马尾、3-盘发、4-头部被遮挡、5-长发、6-光头
  char ageGroup:3;//0-未知、1-儿童、2-少年、3-青年、4-中年、5-老年
  char upperCategory:4;//0-马甲吊带背心、1-衬衫、2-西服、3-毛衣、4-皮衣夹克、5-羽绒服、6-大衣风衣、7-连衣裙、8-T恤、9-无上衣、10-其它
  char upperTexture:3;//0-纯色、1-碎花、2-条纹、3-格子、4-文字、5-其他
  char upperColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-混色、10-其他
  char nonMotorType:3;//0-电瓶车（二轮）、1-自行车、2-三轮车、3-电动三轮、4-摩托车
  char nonMotorColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char nonMotorPassenger:2;//0-无载人、1-载一人、2-载多人
  char nonMotorFrontDirection:3;//0-上、1-左上、2-左、3-左下、4-下、5-右下、6-右、7-右上
  bool gender;//true-男、false-女
  bool sunShade;//有遮阳伞、无遮阳伞
  bool nonMotorBoot;//有后备箱、无后备箱
}NonVehAttr;
typedef std::vector<NonVehAttr> NonVehAttrArray;
class NonVehicleStructured {
public:
    // init nonVehicle Recognizer
    bool init(const std::string& model_dir,const NonVehParas& pas, const int gpu_id);

    //nonVehicle Recognizer inference
    bool inference(const ImgBGRArray& imgs, NonVehAttrArray& nonVehOut);

    //nonVehicle Recognizer release
    void release();
};



/**
 * @brief The FaceRecognizer class
 * Input:ImgBGRArray
 * Output:faceAttrArray
 */
typedef struct {
    //The parameters of FaceRecognizer.
} FaceParas;

typedef struct FaceAttr
{
  char hairstyle:3;//0-未知、1-短发、2-马尾、3-盘发、4-头部被遮挡、5-长发、6-光头
  char ageGroup:3;//0-未知、1-儿童、2-少年、3-青年、4-中年、5-老年
  char facialExpression:2;//0-微笑、1-平静、2-愤怒
  char hat:2;//0-帽子、1-头盔、2-未戴帽子
  char hatColor:4;//0-黑、1-白、2-灰、3-绿、4-深灰、5-红、6-黄、7-蓝、8-紫、9-棕、10-混色、11-其他
  char direction:2;//0-正脸、1-左脸、2-右脸
  bool gender;//true-男、false-女
  bool mask;//带口罩、不带口罩
  bool glasses;//戴眼镜、不戴眼镜
  bool beard;//有胡须、无胡须
} FaceAttr;
typedef std::vector<FaceAttr> FaceAttrArray;
class FaceStructured {
public:
    // init face Recognizer
    bool init(const std::string& model_dir, const FaceParas& pas, const int gpu_id);

  //face Recognizer inference
    bool inference(const ImgBGRArray& imgs, FaceAttrArray& faceOut);

    //face Recognizer release
    void release();
};



/**
 * @brief The plateRecognizer class
 * Input:ImgBGRArray
 * Output:plateAttrArray
 */
typedef struct {
    //The parameters of FaceRecognizer.
} PlateParas;
#define PLATE_LENGTH 10
typedef struct PlateAttr
{
  char plateCategory:4; //0-民用车牌、1-摩托车车牌、2-教练车车牌、3-警用车牌、4-军用车牌、5-港澳车牌、6-武警车牌、7-新能源车牌、8-使领馆车牌
  char plateColor:3;//0-蓝、1-白、2-黄、3-黑、4-绿
  char hasPlate:2;//0-有牌车、1-无车牌、2-污损车牌
  char plateNumber[PLATE_LENGTH];//Specific dimensions need to be given.
}PlateAttr;
typedef std::vector<PlateAttr> PlateAttrArray;
class PlateStructured {
public:
    // init plate Recognizer
    bool init(const std::string& model_dir, const PlateParas& pas, const int gpu_id);

    //plate Recognizer inference
    bool inference(const ImgBGRArray& imgs, PlateAttrArray& plateOut);

    //plate Recognizer release
    void release();
};


/**
 * @brief The pedestrian feature class
 * Input:ImgBGRArray
 * Output:float**
 */
typedef struct {
  int FEATURE_LEN;
    //The parameters of pedestrian feature.
} PedFeatureParas;

//float pedFeature[BANTCH_SIZE][DEEP_FEATURE_LEN];//Specific dimensions need to be given.

class PedestrianFeature {
public:
    // init PedestrianFeature
    bool init(const std::string& model_dir,const PedFeatureParas& pas,const int gpu_id);

    //PedestrianFeature inference
    bool inference(const ImgBGRArray& imgs, float** pedFeatures);

    //PedestrianFeature release
    void release();
private:
  void * extractor_model;
};



/**
 * @brief The face feature class
 * Input:ImgBGRArray
 * Output:float**
 */
typedef struct {
  int FEATURE_LEN;
    //The parameters of face feature.
} FaceFeatureParas;

//float faceFeature[BANTCH_SIZE][DEEP_FEATURE_LEN];//Specific dimensions need to be given.

class FaceFeature {
public:
    // init FaceFeature
    bool init(const std::string& model_dir, const FaceFeatureParas& pas,const int gpu_id);

    //FaceFeature inference
    bool inference(const ImgBGRArray& imgs, float** faceFeatures);

    //FaceFeature release
    void release();
};



/**
 * @brief The vehicle feature class
 * Input:ImgBGRArray
 * Output:float**
 */
typedef struct {
  int FEATURE_LEN;
    //The parameters of vehicle feature.
} VehFeatureParas;

//float vehFeature[BANTCH_SIZE][DEEP_FEATURE_LEN];//Specific dimensions need to be given.

class VehicleFeature {
public:
    // init VehicleFeature
    bool init(const std::string& model_dir,const VehFeatureParas& pas,const int gpu_id);

    //VehicleFeature inference
    bool inference(const ImgBGRArray& imgs, float** vehFeatures);

    //VehicleFeature release
    void release();
private:
  void * extractor_model;
};



/**
 * @brief The nonvehicle feature class
 * Input:ImgBGRArray
 * Output:float**
 */
typedef struct {
  int FEATURE_LEN;
    //The parameters of nonvehicle feature.
} NonVehFeatureParas;

//float nonVehFeature[BANTCH_SIZE][DEEP_FEATURE_LEN];//Specific dimensions need to be given.

class NonVehFeature {
public:
    // init NonVehFeature
    bool init(const std::string& model_dir,const NonVehFeatureParas& pas,const int gpu_id);

    //NonVehFeature inference
    bool inference(const ImgBGRArray& img, float** nonVehFeatures);

    //NonVehFeature release
    void release();
};

#endif /* TOOLS_SO_INCLUDE_BYAVS_API_H_ */
