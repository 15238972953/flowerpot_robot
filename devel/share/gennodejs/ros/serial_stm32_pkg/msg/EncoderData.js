// Auto-generated. Do not edit!

// (in-package serial_stm32_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class EncoderData {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Encoder_Left = null;
      this.Encoder_Right = null;
    }
    else {
      if (initObj.hasOwnProperty('Encoder_Left')) {
        this.Encoder_Left = initObj.Encoder_Left
      }
      else {
        this.Encoder_Left = 0;
      }
      if (initObj.hasOwnProperty('Encoder_Right')) {
        this.Encoder_Right = initObj.Encoder_Right
      }
      else {
        this.Encoder_Right = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EncoderData
    // Serialize message field [Encoder_Left]
    bufferOffset = _serializer.uint32(obj.Encoder_Left, buffer, bufferOffset);
    // Serialize message field [Encoder_Right]
    bufferOffset = _serializer.uint32(obj.Encoder_Right, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EncoderData
    let len;
    let data = new EncoderData(null);
    // Deserialize message field [Encoder_Left]
    data.Encoder_Left = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [Encoder_Right]
    data.Encoder_Right = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'serial_stm32_pkg/EncoderData';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4f445708b5fc7868c7f94d572914b055';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 Encoder_Left
    uint32 Encoder_Right
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EncoderData(null);
    if (msg.Encoder_Left !== undefined) {
      resolved.Encoder_Left = msg.Encoder_Left;
    }
    else {
      resolved.Encoder_Left = 0
    }

    if (msg.Encoder_Right !== undefined) {
      resolved.Encoder_Right = msg.Encoder_Right;
    }
    else {
      resolved.Encoder_Right = 0
    }

    return resolved;
    }
};

module.exports = EncoderData;
