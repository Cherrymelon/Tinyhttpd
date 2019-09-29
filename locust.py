from locust import HttpLocust, TaskSet, task


def index(l):
    l.client.get("/")


class UserBehavior(TaskSet):
    tasks = {index: 2}

    @task
    def index(self):
        # print("Locust instance (%r) executing my_task" % (self.locust))
        self.client.get("/")


class WebsiteUser(HttpLocust):
    task_set = UserBehavior
    min_wait = 5000
    max_wait = 9000
