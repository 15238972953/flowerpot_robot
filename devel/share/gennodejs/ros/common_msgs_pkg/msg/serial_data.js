// Auto-generated. Do not edit!

// (in-package common_msgs_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class serial_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.PWM_Left = null;
      this.PWM_Right = null;
      this.command = null;
      this.clear_encoder = null;
    }
    else {
      if (initObj.hasOwnProperty('PWM_Left')) {
        this.PWM_Left = initObj.PWM_Left
      }
      else {
        this.PWM_Left = 0;
      }
      if (initObj.hasOwnProperty('PWM_Right')) {
        this.PWM_Right = initObj.PWM_Right
      }
      else {
        this.PWM_Right = 0;
      }
      if (initObj.hasOwnProperty('command')) {
        this.command = initObj.command
      }
      else {
        this.command = 0;
      }
      if (initObj.hasOwnProperty('clear_encoder')) {
        this.clear_encoder = initObj.clear_encoder
      }
      else {
        this.clear_encoder = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type serial_data
    // Serialize message field [PWM_Left]
    bufferOffset = _serializer.int8(obj.PWM_Left, buffer, bufferOffset);
    // Serialize message field [PWM_Right]
    bufferOffset = _serializer.int8(obj.PWM_Right, buffer, bufferOffset);
    // Serialize message field [command]
    bufferOffset = _serializer.int8(obj.command, buffer, bufferOffset);
    // Serialize message field [clear_encoder]
    bufferOffset = _serializer.bool(obj.clear_encoder, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type serial_data
    let len;
    let data = new serial_data(null);
    // Deserialize message field [PWM_Left]
    data.PWM_Left = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [PWM_Right]
    data.PWM_Right = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [command]
    data.command = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [clear_encoder]
    data.clear_encoder = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'common_msgs_pkg/serial_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '23aa005a44d993632cdb1134fc156a3a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 PWM_Left
    int8 PWM_Right
    int8 command
    bool clear_encoder
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new serial_data(null);
    if (msg.PWM_Left !== undefined) {
      resolved.PWM_Left = msg.PWM_Left;
    }
    else {
      resolved.PWM_Left = 0
    }

    if (msg.PWM_Right !== undefined) {
      resolved.PWM_Right = msg.PWM_Right;
    }
    else {
      resolved.PWM_Right = 0
    }

    if (msg.command !== undefined) {
      resolved.command = msg.command;
    }
    else {
      resolved.command = 0
    }

    if (msg.clear_encoder !== undefined) {
      resolved.clear_encoder = msg.clear_encoder;
    }
    else {
      resolved.clear_encoder = false
    }

    return resolved;
    }
};

module.exports = serial_data;
