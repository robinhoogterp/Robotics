import asyncio
import socketio
import json
import cv2
from greppelState import greppelState
import base64
import numpy as np

cam = cv2.VideoCapture('/dev/video0')  # LINUX
# cam = cv2.VideoCapture(0, cv2.CAP_DSHOW)  # Windows
lower_blue = np.array([100, 100, 100])
upper_blue = np.array([140, 255, 255])
sio = socketio.AsyncClient()
encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 40]
state = greppelState()


@sio.event
async def connect():
    print('connection established')
    task = sio.start_background_task(background_task)
    # await send_cam()


@sio.event
async def reconnect():
    print('reconnected')
    task = sio.start_background_task(background_task)


# Word constant uitgevoerd na de startup tasks.
async def background_task():
    try:
        while True:
            await send_state()
            await send_cam()
            # await send_state()
            await asyncio.sleep(0.1)
    except Exception as e:
        print(e)


# Verstuurd telemetrie naar de server
async def send_state():
    state.getState()

    stateJson = state.getJson()
    await sio.emit("greppelstate", stateJson)


# Verstuurd een camera frame naar de website
async def send_cam():
    ret, frame = cam.read()
    print(frame.shape)
    #frame = cv2.imread('test2.png')

    img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    bluemask = cv2.inRange(img, lower_blue, upper_blue)
    ret, thresh, = cv2.threshold(bluemask, 0, 255, cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) != 0:
        for cnr in range(len(contours)):
            area = cv2.contourArea(contours[cnr])
            if area > 500:
                cnt = contours[cnr]
                moments = cv2.moments(cnt)
                cx = int(moments['m10']/moments['m00'])
                state.passXPos(cx)
                # print(cx)
                color = (0, 0, 255)
                cv2.circle(frame, (cx, 250), 6, color, -1)
                cv2.drawContours(frame, contours, cnr, color, 4)


    # rescale image to send
    scale_percent = 100  # percent of original size
    width = int(frame.shape[1] * scale_percent / 100)
    height = int(frame.shape[0] * scale_percent / 100)
    dim = (width, height)
    img = cv2.resize(frame, dim, interpolation=cv2.INTER_AREA)

    # encode to jpg to reduce size, convert to base64
    img_encoded = cv2.imencode('.jpg', img, encode_param)[1]
    data = base64.b64encode(img_encoded)

    await sio.emit('image', data)


@sio.event
async def disconnect():
    print('disconnected from server')
    # cam.release()
    cv2.destroyAllWindows()


async def main():
    await sio.connect('http://greppel.tech:3000')
    await sio.wait()
    # cam.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    asyncio.run(main())