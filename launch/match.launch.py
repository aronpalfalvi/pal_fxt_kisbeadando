from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    goal_rate = LaunchConfiguration('goal_rate')
    topic = LaunchConfiguration('topic')
    ns = LaunchConfiguration('ns')

    return LaunchDescription([
        DeclareLaunchArgument(
            'goal_rate', default_value='2.5',
            description='Poisson átlag (várható gól/meccs) a publisherhez.'
        ),
        DeclareLaunchArgument(
            'topic', default_value='/focimeccsek',
            description='A topik neve, amin a gólszám megy.'
        ),
        DeclareLaunchArgument(
            'ns', default_value='',
            description='Namespace a node-okhoz.'
        ),
        Node(
            package='focimeccs',
            executable='match_publisher',
            namespace=ns,
            name='match_publisher',
            parameters=[{'goal_rate': goal_rate}],
            remappings=[('focimeccsek', topic), ('/focimeccsek', topic)],
            output='screen',
        ),
        Node(
            package='focimeccs',
            executable='match_subscriber',
            namespace=ns,
            name='match_subscriber',
            remappings=[('focimeccsek', topic), ('/focimeccsek', topic)],
            output='screen',
        ),
    ])