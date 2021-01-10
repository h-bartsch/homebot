xterm -e "g++ pick_objects.cpp -o pick_objects -I/opt/ros/kinetic/include -L/opt/ros/kinetic/lib -lroscpp -lrostime -lrosconsole -lroscpp_serialization -lboost_system -lboost_thread -lpthread -lactionlib"
sleep 5
xterm -e "g++ add_markers.cpp -o add_markers -I/opt/ros/kinetic/include -L/opt/ros/kinetic/lib -lroscpp -lrostime -lrosconsole -lroscpp_serialization"