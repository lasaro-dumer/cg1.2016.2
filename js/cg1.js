var app = angular.module('cg1App', ['ngRoute']);

app.controller('cg1Controller', function($scope, $route, $routeParams, $location) {
        $scope.$route = $route;
        $scope.$location = $location;
        $scope.$routeParams = $routeParams;
    })
    .controller('ProjectController', function($scope, $routeParams) {
        $scope.name = 'ProjectController';
        $scope.params = $routeParams;
    })
    .config(function($routeProvider, $locationProvider) {
        $routeProvider
            .when('/Blog/:project/files', {
                templateUrl: function(params) {
                    return 'cg1.2016.2/blog/'+params.project+'/files.html';
                },
                controller: 'ProjectController'
            })
            .when('/Blog/:project/diary/:entry', {
                templateUrl: function(params) {
                    return 'cg1.2016.2/blog/'+params.project+'/' + params.entry + '.html';
                },
                controller: 'ProjectController'
            });
        // configure html5 to get links working on jsfiddle
        $locationProvider.html5Mode(true);
    });
