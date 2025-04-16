// Auto-generated. Do not edit!

// (in-package radar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let radar = require('./radar.js');

//-----------------------------------------------------------

class Array {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Array = null;
    }
    else {
      if (initObj.hasOwnProperty('Array')) {
        this.Array = initObj.Array
      }
      else {
        this.Array = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Array
    // Serialize message field [Array]
    // Serialize the length for message field [Array]
    bufferOffset = _serializer.uint32(obj.Array.length, buffer, bufferOffset);
    obj.Array.forEach((val) => {
      bufferOffset = radar.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Array
    let len;
    let data = new Array(null);
    // Deserialize message field [Array]
    // Deserialize array length for message field [Array]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.Array = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.Array[i] = radar.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 9 * object.Array.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'radar_msgs/Array';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '997f34d9f4575d60cbee5bcd6077246d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    radar[] Array
    ================================================================================
    MSG: radar_msgs/radar
    int8 n
    float32 r
    float32 phi
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Array(null);
    if (msg.Array !== undefined) {
      resolved.Array = new Array(msg.Array.length);
      for (let i = 0; i < resolved.Array.length; ++i) {
        resolved.Array[i] = radar.Resolve(msg.Array[i]);
      }
    }
    else {
      resolved.Array = []
    }

    return resolved;
    }
};

module.exports = Array;
