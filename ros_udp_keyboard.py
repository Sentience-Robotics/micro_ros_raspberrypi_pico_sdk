#!/usr/bin/env python3

import socket
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32

LOCAL_PORT = 5005
BUFFER_SIZE = 1024
speed = 5

class UDPKeyPublisher(Node):
    def __init__(self):
        super().__init__('udp_keyboard_publisher')
        self.publisher = self.create_publisher(Int32, 'rp2040_listener_topic', 10)
        self.angle = 90
        self.get_logger().info(f"Listening for UDP keys on port {LOCAL_PORT}")
        # Setup UDP socket (non-blocking)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("", LOCAL_PORT))
        self.sock.setblocking(False)
        # Timer for polling UDP socket at 100 Hz
        timer_hz = 100
        self.timer = self.create_timer(1.0 / timer_hz, self.tick)

    def tick(self):
        try:
            data, addr = self.sock.recvfrom(BUFFER_SIZE)
        except BlockingIOError:
            return  # no data ready
        key = data.decode(errors='ignore').strip()
        self.get_logger().debug(f"UDP received key '{key}' from {addr}")
        if key == '123':
            self.angle = max(0, self.angle - speed)
            self.send_angle()
        elif key == '124':
            self.angle = min(180, self.angle + speed)
            self.send_angle()
        elif key == 'esc':
            self.get_logger().info("ESC received → shutting down")
            rclpy.shutdown()

    def send_angle(self):
        msg = Int32(data=self.angle)
        self.publisher.publish(msg)
        self.get_logger().info(f"Published angle: {self.angle}")

    def destroy_node(self):
        # Clean up
        self.sock.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = UDPKeyPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("KeyboardInterrupt → shutting down")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
