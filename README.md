# focimeccs ROS 2 package

Ez a ROS 2 Humble csomag két fő node-ot tartalmaz, amelyek egy focimeccs eseményeit szimulálják:

1. **/match_publisher**  
   Ez a node rendszeresen üzeneteket publikál egy focimeccs eseményeiről (gólok száma).  
   A node a `std_msgs/String` típusú üzeneteket küldi a `/focimeccs` témára.  

2. **/match_subscriber**  
   Ez a node feliratkozik a `/focimeccs` üzeneteire, és a kapott eseményeket a terminálon jeleníti meg (pl. ha egy mérkőzésen több, mint 6 gól született, akkor azt írja ki, hogy 'gólzápor', ha 0 akkor pedig azt, hogy 'unalmas mérkőzés').  

---

## Telepítés

A workspace neve `~/ros2_ws/`:

```bash
cd ~/ros2_ws/src
git clone https://github.com/aronpalfalvi/pal_fxt_kisbeadando.git
```

---

## Fordítás

```bash
cd ~/ros2_ws
colcon build --packages-select focimeccs --symlink-install
```

---

## Futatás

Minden új terminálban forrásold a workspace-t:

```bash
source ~/ros2_ws/install/setup.bash
```

### 1. Publisher node indítása

```bash
ros2 run focimeccs match_publisher
```

### 2. Subscriber node indítása

```bash
ros2 run focimeccs match_subscriber
```

### 3. Launch file használata

A két node együtt is indítható:

```bash
ros2 launch focimeccs match.launch.py
```

---

## Diagram

```mermaid
graph LR;

pub([/match_publisher]):::red --> topic[/focimeccs\nstd_msgs/String/]:::lighttopic
topic --> sub([/match_subscriber]):::red

classDef lighttopic fill:#34aec5,stroke:#152742,stroke-width:2px,color:#152742  
classDef red fill:#ef4638,stroke:#152742,stroke-width:2px,color:#fff

```
