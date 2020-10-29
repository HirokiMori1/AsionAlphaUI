#ifndef DEFINE_H
#define DEFINE_H

#define MAPS_FILEPATH "/home/kufushatec/catkin_ws/src/ros_start/maps"
#define SH_FILEPATH   "/home/kufushatec/catkin_ws/src/ros_start/cmd/"

#define RESOLUTION_NUM 0
#define NEGATE_NUM 1
#define OCCUPIED_THRESH_NUM 2
#define FREE_THRESH_NUM 3

#define X_LENGTH_NUM 0
#define Y_LENGTH_NUM 1
#define X_ANGLE_NUM 2
#define Y_ANGLE_NUM 3

#define IMAGE_EXTENSION ".pgm"
#define ROUTE_EXTENSION ".yaml"

#define IMAGE_SIZE 200

#define PATH_FORMAT "%s%s"
#define NAME_FORMAT "%s/%s%s"
#define COMMENT_FORMAT "%s%s"
#define CONFIRM_FORMAT "%s%s%s"
#define MAKEROOT_FORMAT "%s%s %s %s"
#define MAPS_ROUTE_FORMAT "%s/%s"
#define MAPS_YAML_FORMAT "%s/%s/%s%s"

#define KILL_NODE_COMMAND "rosnode kill --all"

#define SH_MAKEROOT "make_auto_route.sh"  // hikisuu naosu
#define SH_POWER_ON "power_on.sh"
#define SH_ROUTES   "routes.sh"
#define SH_STOP     "stop.sh"
#define SH_MAKEMAP  "make_map.sh"
#define SH_LOADMAP  "load.sh"

#define ROUTE_YAML  "route999.yaml"

#define COPYRIGHT "Copyrigth(c) Kufusha Inc., 2020, All Rights Reserved."

#endif // DEFINE_H
