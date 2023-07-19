
#include <iostream>
#include <string>

/**
 * @brief 简单概述
 * @brief 状态基类
 */
class Status {
public:
  Status() {}
  virtual void ShowStepTip() = 0;
};

/**
 * @brief 简单概述
 * @brief 车辆驶入状态
 */
class CarInStatus : public Status {
public:
  CarInStatus() {}
  void ShowStepTip() { std::cout << "请驶入指定位置" << std::endl; }
};

/**
 * @brief 简单概述
 * @brief 驻车状态
 */
class CarStopStatus : public Status {
public:
  CarStopStatus() {}
  void ShowStepTip() { std::cout << "熄火，挂P档，拉手刹" << std::endl; }
};

/**
 * @brief 简单概述
 * @brief 加油状态
 */
class AddOilStatus : public Status {
public:
  AddOilStatus() {}
  void ShowStepTip() { std::cout << "拾起油枪加注汽油" << std::endl; }
};

/**
 * @brief 简单概述
 * @brief 加油完成状态
 */
class FinishAddStatus : public Status {
public:
  FinishAddStatus() {}
  void ShowStepTip() { std::cout << "放好油枪" << std::endl; }
};

/**
 * @brief 简单概述
 * @brief 车辆驶离状态
 */
class CarOutStatus : public Status {
public:
  CarOutStatus() {}
  void ShowStepTip() { std::cout << "请驶离换电站" << std::endl; }
};

/**
 * @brief 简单概述
 * @brief 状态管理类
 */
class StatusMgr {
public:
  StatusMgr() {}
  void SetStatus(Status *s) { m_pStatus = s; }
  void ShowCurTip() { m_pStatus->ShowStepTip(); }

private:
  Status *m_pStatus;
};