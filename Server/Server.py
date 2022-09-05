from flask import Flask, jsonify
from flask_cors import CORS
from LaneDetection import *

app = Flask(__name__)
CORS(app)
# for blue color
low=np.array([40,70,0])
high=np.array([150,255,255])
@app.route('/')
def main():
    return "main Page"

@app.route('/DetectAngle', methods=['GET'])
def process():
    image=GetImageFromMobile()
    laneLines =LaneDetection(image, low, high)
    laneLinesImage = LinesDisplaying(image, laneLines)
    steeringAngle= SteeringAngle(image, laneLines)
    currentAngle = steeringAngle
    print(currentAngle)
    finalImage = displayHeadingLine(laneLinesImage, currentAngle)
    cv2.imwrite('final.jpg', finalImage)


    if (0<currentAngle<70):
        currentAngle='R'   
  
    elif (115<=currentAngle<180): 
        currentAngle='L'        
    elif (70<=currentAngle<115 or currentAngle==-90):
        currentAngle='F'
    else:
        currentAngle='S'   

    print(currentAngle)    

    return currentAngle


if __name__ == '__main__':
    app.run(host='************',port=3000,debug=True)

