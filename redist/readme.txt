Please do not forget to install
1) pip
2) pip install dmgbuild
3) pip install lxml
Last one can be problem as libxml2 headers are not linked properly by brew
Please use smth like this
export C_INCLUDE_PATH=/usr/local/Cellar/libxml2/2.9.1/include/libxml2:$C_INCLUDE_PATH


4) Do not forget to make downloads/ folder on target host
