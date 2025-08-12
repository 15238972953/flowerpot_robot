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

class encoder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.right_distance = null;
      this.left_distance = null;
    }
    else {
      if (initObj.hasOwnProperty('right_distance')) {
        this.right_distance = initObj.right_distance
      }
      else {
        this.right_distance = 0.0;
      }
      if (initObj.hasOwnProperty('left_distance')) {
        this.left_distance = initObj.left_distance
      }
      else {
        this.left_distance = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type encoder
    // Serialize message field [right_distance]
    bufferOffset = _serializer.float32(obj.right_distance, buffer, bufferOffset);
    // Serialize message field [left_distance]
    bufferOffset = _serializer.float32(obj.left_distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type encoder
    let len;
    let data = new encoder(null);
    // Deserialize message field [right_distance]
    data.right_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [left_distance]
    data.left_distance = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'common_msgs_pkg/encoder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8667235667f6c2bbcdbec984ca8922d9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 right_distance
    float32 left_distance
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new encoder(null);
    if (msg.right_distance !== undefined) {
      resolved.right_distance = msg.right_distance;
    }
    else {
      resolved.right_distance = 0.0
    }

    if (msg.left_distance !== undefined) {
      resolved.left_distance = msg.left_distance;
    }
    else {
      resolved.left_distance = 0.0
    }

    return resolved;
    }
};

module.exports = encoder;
