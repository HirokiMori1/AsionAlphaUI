#ifndef DEFINE_H
#define DEFINE_H

#define MAPS_FILEPATH "/home/kufushatec/asion_ws/src/asion_main/maps"
#define SH_FILEPATH   "/home/kufushatec/asion_ws/src/asion_main/cmd/"
#define ASION_IMG     "/home/kufushatec/AsionAlphaUI/image/Asion.png"
#define KUFUSHA_IMG   "/home/kufushatec/AsionAlphaUI/image/kufusha.png"
#define FDESIGN_IMG   "/home/kufushatec/AsionAlphaUI/image/FDesign.png"
#define CARROT_IMG    "/home/kufushatec/AsionAlphaUI/image/carrotsystems.png"
#define LOAD_IMG      "/home/kufushatec/AsionAlphaUI/image/load.png"
#define START_IMG     "/home/kufushatec/AsionAlphaUI/image/start.png"
#define RESTART_IMG   "/home/kufushatec/AsionAlphaUI/image/restart.png"
#define STOP_IMG      "/home/kufushatec/AsionAlphaUI/image/stop.png"

#define RESOLUTION_NUM      0
#define NEGATE_NUM          1
#define OCCUPIED_THRESH_NUM 2
#define FREE_THRESH_NUM     3

#define X_LENGTH_NUM 0
#define Y_LENGTH_NUM 1
#define X_ANGLE_NUM  2
#define Y_ANGLE_NUM  3

#define IMAGE_SIZE 200

#define IMAGE_EXTENSION ".pgm"
#define ROUTE_EXTENSION ".yaml"

#define PATH_FORMAT       "%s%s"
#define NAME_FORMAT       "%s/%s%s"
#define COMMENT_FORMAT    "%s%s"
#define CONFIRM_FORMAT    "%s%s%s"
#define MAKEROOT_FORMAT   "%s%s %s %s"
#define MAPS_ROUTE_FORMAT "%s/%s"
#define MAPS_YAML_FORMAT  "%s/%s/%s%s"

#define KILL_NODE_COMMAND "rosnode kill --all"

#define SH_NAVIGATION     "navigation.sh"
#define SH_START          "start.sh"
#define SH_RELEASE_BUMPER "release_bumper.sh"
#define SH_STOP           "stop.sh"

#define ROUTE_YAML  "route999.yaml"

#define NAVIGATION_MSG     "Asionはスタート位置にいますか？"
#define START_MSG          "Asionはスタート位置にいますか？"
#define RELEASE_BUMPER_MSG "再スタートします。Asionの周囲は問題ないですか？"

#define COPYRIGHT "Copyrigth(c) Kufusha Inc., 2020, All Rights Reserved."
#define OSSLICFILE "/home/kufushatec/AsionAlphaUI/licenses/third-party-licenses.txt"

#endif // DEFINE_H
