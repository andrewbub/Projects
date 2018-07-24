import unittest
import requests
import json

class TestColleges(unittest.TestCase):

    PORT_NUM = '51035' #change port number to match your port number
    print("Testing Port number: ", PORT_NUM)
    SITE_URL = 'http://student04.cse.nd.edu:' + PORT_NUM
    COLLEGES_URL = SITE_URL + '/colleges/'
    RESET_URL = SITE_URL + '/reset/'

    def reset_data(self):
        m = {}
        r = requests.put(self.RESET_URL, data = json.dumps(m))

    def is_json(self, resp):
        try:
            json.loads(resp)
            return True
        except ValueError:
            return False

    def test_colleges_get(self):
        #print('Test colleges_get')
        self.reset_data()
        key = "University of Notre Dame"
        r = requests.get(self.COLLEGES_URL + str(key))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['Name'], 'University of Notre Dame')
        self.assertEqual(resp['City'], 'Notre Dame')
        self.assertEqual(resp['State'], 'IN')
        self.assertEqual(resp['WebURL'], 'www.nd.edu')
        self.assertEqual(resp['FinURL'], 'financialaid.nd.edu')
        self.assertEqual(resp['Region'], '3')
        self.assertEqual(resp['ACT'], '33')
        self.assertEqual(resp['SAT'], '1455')
        self.assertEqual(resp['Population'], '8425')
        self.assertEqual(resp['Cost'], '62427')

    def test_colleges_put(self):
        #print('Test colleges_put')
        self.reset_data()
        key = "University of Notre Dame"

        r = requests.get(self.COLLEGES_URL + str(key))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['City'], 'Notre Dame')
        self.assertEqual(resp['State'], 'IN')

        m = {}
        m['college'] = 'University of Notre Dame'
        m['info'] = ['Notre Dame', 'IN', 'www.nd.edu', 'financialaid.nd.edu', '3', '36', '1600', '8425', '62427']
        r = requests.put(self.COLLEGES_URL + str(key), data = json.dumps(m))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['result'], 'success')

        r = requests.get(self.COLLEGES_URL + str(key))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['ACT'], m['info'][6])
        self.assertEqual(resp['SAT'], m['info'][7])

    def test_colleges_delete(self):
        #print('Test colleges_delete')
        self.reset_data()
        key = "University of Michigan-Ann Arbor"

        m = {}
        r = requests.delete(self.COLLEGES_URL + str(key), data = json.dumps(m))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['result'], 'success')

        r = requests.get(self.COLLEGES_URL + str(key))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['result'], 'error')

if __name__ == "__main__":
    unittest.main()

