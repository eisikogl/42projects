all: compile 

compile:
	@docker-compose up --build

up:
	@docker-compose up

down:
	@docker-compose down

re: clean all

clean:
	-@docker stop $$(docker ps -qa)
	-@docker rm $$(docker ps -qa)
	-@docker rmi -f $$(docker images -qa)
	-@docker volume rm $$(docker volume ls -q)
	-@docker system prune -af
