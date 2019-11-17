import boto3
MTURK_SANDBOX = 'https://mturk-requester-sandbox.us-east-1.amazonaws.com'
mturk = boto3.client('mturk',
   aws_access_key_id = "",
   aws_secret_access_key = "",
   region_name='us-east-1',
   endpoint_url = MTURK_SANDBOX
)

question = open(name='question.xml',mode='r').read()
new_hit = mturk.create_hit(
    Title = 'Could you interpret the following audio?',
    Description = 'What can you hear from this audio?',
    Keywords = 'audio, interpret',
    Reward = '0.01',
    MaxAssignments = 1,
    LifetimeInSeconds = 172800,
    AssignmentDurationInSeconds = 600,
    AutoApprovalDelayInSeconds = 14400,
    Question = question,
)
print "A new HIT has been created. You can preview it here:"
print "https://workersandbox.mturk.com/mturk/preview?groupId=" + new_hit['HIT']['HITGroupId']
print "HITID = " + new_hit['HIT']['HITId'] + " (Use to Get Results)"
# Remember to modify the URL above when you're publishing
# HITs to the live marketplace.
# Use: https://worker.mturk.com/mturk/preview?groupId=

# print "I have $" + mturk.get_account_balance()['AvailableBalance'] + " in my Sandbox account"
