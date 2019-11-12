# google_api_python.py
# - run and test google api using wav file
#
# Originally copied from Google API Document
# Modified by Juan Lee

import io, os, sys

if len(sys.argv) < 3:
    print("Usage: %s filename sample_rate" % (sys.argv[0]))
    sys.exit(-1)

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

# Instantiates a client
client = speech.SpeechClient()

# The name of the audio file to transcribe
file_name = sys.argv[1]

# Loads the audio into memory
with io.open(file_name, 'rb') as audio_file:
    content = audio_file.read()
    audio = types.RecognitionAudio(content=content)

config = types.RecognitionConfig(
    encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
    sample_rate_hertz=int(sys.argv[2]),
    language_code='en-US')

# Detects speech in the audio file
response = client.recognize(config, audio)

for result in response.results:
    print(result.alternatives[0].transcript)
